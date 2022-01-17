#include <stdio.h>
#include <assert.h>

typedef unsigned float_bits;

float_bits float_twice(float_bits f)
{
    unsigned sign = f >> 31;
    unsigned exp = f >> 23 & 0xFF;
    unsigned frac = f & 0x7FFFFF;
    unsigned rest = f & 0x7FFFFFFF;

    int addition = (frac & 0x3) == 0x3; // round to even

    int is_NaN_oo = (exp == 0xFF);
    if (is_NaN_oo)
        return f;

    if (exp == 0)
    {
        frac >>= 1;
        frac += addition;
    }
    else if (exp == 1)
    {
        exp = 0;
        rest >>= 1;
        rest += addition;
        frac = rest & 0x7FFFFF;
    }
    else
    {
        exp -= 1;
    }

    return sign << 31 | exp << 23 | frac;
}

void main()
{
}