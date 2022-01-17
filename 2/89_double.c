#include <stdio.h>
#include <assert.h>
#include <limits.h>

int A(int x, double dx)
{
    // right
    return (float)x == (float)dx;
}

int B(int x, double dx, int y, double dy)
{
    // y cannot be INT_MIN
    return dx - dy == (double)(x - y);
}

int C(double dx, double dy, double dz)
{
    // right
    return (dx + dy) + dz == dx + (dy + dz);
}

int D(double dx, double dy, double dz)
{
    // wrong 存在溢出
    return (dx * dy) * dz == dx * (dy * dz);
}

int E(double dx, double dz)
{
    // cannot have 0
    return dx / dx == dz / dz;
}

void main()
{
    assert(!B(0, 0.0, INT_MIN, INT_MIN));
    assert(!E(1.0, 0.0));
}
