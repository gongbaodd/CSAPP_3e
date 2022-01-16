#include <stdio.h>
#include <assert.h>

int A(int k)
{
    // 1^{w-k}0^k
    return -1 << k;
}

int B(int j, int k)
{
    // 0^{w-k-j}1^k0^j
    return ~A(k) << j;
}

void main()
{
    assert(A(8) == 0xFFFFFF00);
    assert(B(16, 8) == 0x00FFFF00);
}