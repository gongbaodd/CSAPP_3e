#include <stdio.h>
#include <assert.h>

typedef unsigned float_bits;

float_bits float_negate(float_bits f)
{
    unsigned sign = f >> 31;
    unsigned exp = f >> 23 & 0xFF;
    unsigned frac = f & 0x7FFFFF;

    int is_NaN = (exp == 0xFF) && (frac != 0);
    if (is_NaN)
    {
        return f;
    }

    return (~sign << 31) | (exp << 23) | frac;
}

void main()
{
    assert(float_negate(0x89) == 0x80000089);
}
