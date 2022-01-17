#include <stdio.h>
#include <assert.h>

typedef unsigned float_bits;

float u2f(unsigned u)
{
    return *(float *)&u;
}

int float_f2i(float_bits f)
{
    unsigned sign = f >> 31;
    unsigned exp = f >> 23 & 0xFF;
    unsigned frac = f & 0x7FFFFF;
    unsigned bias = 0x7F; // 2^7-1

    int result;
    unsigned E;
    unsigned M;

    if (exp < bias)
    {
        result = 0; // 2^{-x}
    }
    else if (exp >= 31 + bias)
    {
        result = 0x80000000;
    }
    else
    {
        E = exp - bias;
        M = frac | 0x800000;
        if (E > 23)
        {
            result = M << (E - 23);
        }
        else
        {
            result = M >> (23 - E);
        }
    }

    return sign ? -result : result;
}
