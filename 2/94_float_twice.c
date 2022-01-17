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
        frac = 0;
    }
    else if (exp == 0)
    {
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
}