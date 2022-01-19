#include <stdio.h>
#include <assert.h>
#include <limits.h>

typedef unsigned float_bits;

int bits_length(int i)
{
    // Return 32 when i<0
    if (i & INT_MIN != 0)
    {
        return 32;
    }

    int length = 0;
    unsigned u = (unsigned)i;
    while (u >= (1 << length))
    {
        length++;
    }
    return length;
}

unsigned generate_mask(int len)
{
    return (unsigned)-1 >> (32 - len);
}

float_bits float_i2f(int i)
{
    unsigned sign, exp, frac, exp_frac;
    unsigned bias = 0x7F;

    if (i == 0)
    {
        return (float_bits)i;
    }

    if (i == INT_MIN)
    {
        sign = 1;
        exp = 31 + bias; // (E=31)
        frac = 0;
        return sign << 31 | exp << 23 | frac; // -2^31
    }

    sign = 0;
    if (i < 0)
    {
        sign = 1;
        i = -i;
    }

    int length = bits_length(i);
    int flength = length - 1; // fraction length
    unsigned mask = generate_mask(flength);
    unsigned f = i & mask;   // get fraction part
    exp = bias + length - 1; // E == len(i) - 1

    if (flength <= 23)
    {
        frac = f << (23 - flength); // right pad 0s
        exp_frac = exp << 23 | frac;
    }
    else
    {
        // flength > 23
        int offset = flength - 23; // dessert length
        frac = f >> offset;        // needed fraction part
        exp_frac = exp << 23 | frac;

        int round_mid = 1 << (offset - 1);          // 10...0
        int round_part = f & generate_mask(offset); // xx...x

        if (round_part < round_mid)
        {
            // dessert
        }
        else if (round_part > round_mid)
        {
            exp_frac += 1;
        }
        else
        {
            if ((frac & 0x1) == 1)
            {
                exp_frac += 1;
            }
        }
    }
    return sign << 31 | exp_frac;
}

void main()
{
    /* Test bits_length */
    // assert(bits_length(-1) == 32);
    // assert(bits_length(INT_MIN) == 32);
    // assert(bits_length(0) == 0);
    // assert(bits_length(3) == 2);
    // assert(bits_length(23) == 5);

    /* Test generate_mask */
    // assert(generate_mask(3) == 0x7);
    // assert(generate_mask(9) == 0x1FF);
    // assert(generate_mask(31) == 0x7FFFFFFF);

    // /* Test float_i2f */
    // assert(float_i2f(0) == 0x0);
    // assert(float_i2f(INT_MIN) == 0xCF000000);
    // assert(float_i2f(0x00359141) == 0x4A564504);
    // assert(float_i2f(-98765) == 0xC7C0E680);
}