#include <stdio.h>
#include <assert.h>

typedef unsigned float_bits;

float_bits float_twice(float_bits f)
{
    unsigned sign = f >> 31;
    unsigned exp = f >> 23 & 0xFF;
    unsigned frac = f & 0x7FFFFF;

    int is_NaN_oo = (exp == 0xFF);

    if (is_NaN_oo)
        return f;

    if (exp == 0xFF - 1)
    {
        // overflow
        frac = 0;
    }
    else if (exp == 0)
    {
        // i.e. the number is 0b0.1;
        // V_old = 2^{1-bias}*0b0.1 = 2^{-bias}
        // V_new = 2^{1-bias}*0b1.0 = 2^{1-bias} = 2*V_old
        frac <<= 1;
    }
    else
    {
        exp += 1;
    }

    return sign << 31 | exp << 23 | frac;
}

void main()
{
    assert(float_twice(0x3dcccccd) == 0x3e4ccccd);
}