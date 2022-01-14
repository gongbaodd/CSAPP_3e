#include <stdio.h>
#include <assert.h>
#include <limits.h>

// x/2^k
int divide_power2(int x, int k)
{

    // round up
    x = x + (1 << k) - 1;

    return x >> k;
}

void main()
{
    int x = 0x80000007;
    assert(divide_power2(x, 1) == x / 2);
    assert(divide_power2(x, 2) == x / 4);
}