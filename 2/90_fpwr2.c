#include <stdio.h>
#include <assert.h>
#include <math.h>

/*
    k = 8
    n = 23
    bias = 2^7 - 1
*/

float u2f(unsigned x)
{
    return *(float *)&x;
}

float fpwr2(int x) // 2^x
{
    /* Result exponent and fraction */
    unsigned exp, frac;
    unsigned u;

    if (x < -pow(2, 7) - 21)
    {
        /* Too small. Return 0.0 */
        // M=2^{-23}; E=1-2^7+1; V=2^{2-2^7}*2^{-23}=2^{-21-2^7}
        exp = 0;
        frac = 0;
    }
    else if (x < 2 - pow(2, 7))
    {
        /* Denormalized result */
        // the right operator is the least normalized
        // e=00...1; f=0...0; E=1-2^7+1=2-2^7; M=1.0; V=2-2^7
        exp = 0;
        // 2^x=(1000...0)*2^{-23}*2^{1-pow(2,7)+1}=(10...0)*2^{-pow(2,7)-21}
        // (10..0)=2^{x+pow(2,7)+21}
        frac = 1 << (unsigned)(x + pow(2, 7) + 21);
    }
    else if (x < pow(2, 7))
    {
        /* Normalized result */
        // the right operator
        // e=11...0; f=1....1; E=2^7-1; M=2-2^{-23}<2; V=2^{2^7-1}*2=2^{2^7}
        exp = pow(2, 7) - 1 + x;
        frac = 0;
    }
    else
    {
        /* Too big, return +oo */
        exp = 0xFF;
        frac = 0;
    }

    u = exp << 23 | frac;
    return u2f(u);
}

void main()
{
    assert(fpwr2(0) == powf(2, 0));
    assert(fpwr2(100) == powf(2, 100));
    assert(fpwr2(-100) == powf(2, -100));
    assert(fpwr2(10000) == powf(2, 10000));
    assert(fpwr2(-10000) == powf(2, -10000));
}