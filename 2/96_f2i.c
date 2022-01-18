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

    // V = 2^E*M;
    if (exp < bias)
    {
        // E=e-bias; E<1 => V<1
        result = 0;
    }
    else if (exp >= 31 + bias)
    {
        // MAX_INT == 2^31 => E<31 => e-bias<31 otherwise overflow
        result = 0x80000000;
    }
    else
    {
        E = exp - bias;
        M = frac | 0x800000; // IntM = M<<23
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

int main()
{
    assert(float_f2i(0x98765432) == (int)u2f(0x98765432));
    assert(float_f2i(0x19802385) == (int)u2f(0x19802385));
    assert(float_f2i(0x78000087) == 0x80000000);
    assert(float_f2i(0x8F088888) == (int)u2f(0x8F088888));
}
