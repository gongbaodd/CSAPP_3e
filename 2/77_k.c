#include <stdio.h>
#include <assert.h>

int A(int x)
{
    return (x << 4) + x;
}

int B(int x)
{
    return -(x << 3) + x;
}

int C(int x)
{
    return (x << 6) - (x << 2);
}

int D(int x)
{
    return (x << 4) - (x << 7);
}

void main()
{
    int x = 0x12345678;

    assert(A(x) == 17 * x);
    assert(B(x) == -7 * x);
    assert(C(x) == 60 * x);
    assert(D(x) == -112 * x);
}