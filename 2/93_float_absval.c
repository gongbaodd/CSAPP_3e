#include <stdio.h>
#include <assert.h>

typedef unsigned float_bits;

float_bits float_absval(float_bits f)
{
    unsigned exp = f >> 23 & 0xFF;
    unsigned frac = f & 0x7FFFFF;

    int is_NaN = (exp == 0xFF) && (frac != 0);

    if (is_NaN)
    {
        return f;
    }

    return (0 << 31) | exp << 23 | frac;
}

void main()
{
    assert(float_absval(0x80000089) == 0x89);
}