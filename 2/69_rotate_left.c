#include <stdio.h>
#include <assert.h>

unsigned rotate_left(unsigned x, int n)
{
    int w = sizeof(int) << 3;
    // it was suppose to be `x << n | x >> (w - n)`
    // but if n=0, then x>>32 wont work
    return x << n | (x >> (w - n - 1) >> 1);
}

void main()
{
    assert(rotate_left(0x12345678, 4) == 0x23456781);
}
