#include <stdio.h>
#include <assert.h>
#include <limits.h>

int A(int x, int y)
{
    // x cannot be INT_MIN
    return (x < y) == (-x > -y);
}

int B(int x, int y)
{
    // always true
    return ((x + y) << 4) + y - x == 17 * y + 15 * x;
}

int C(int x, int y)
{
    // always true
    // (~x + 1) + (~y + 1) - 1 = -x + -y -1 = -(x+y) -1 = ~(x+y)
    return ~x + ~y + 1 == ~(x + y);
}

int D(int x, int y)
{
    // true

    unsigned ux = (unsigned)x;
    unsigned uy = (unsigned)y;

    return (ux - uy) == -(unsigned)(y - x);
}

int E(int x)
{
    /// true
    return (x >> 2) << 2 <= x;
}

void main()
{
    // assert(!A(INT_MIN, 1)); //?
}