#include <stdio.h>
#include <assert.h>

/*
int bad_int_size_is_32()
{
    int set_msb = 1 << 31;
    int beyond_msb = 1 << 32; // 32 is larger than the width of 1

    return set_msb && !beyond_msb;
}
*/

int int_size_is_32()
{
    int set_msb = 1 << 31;
    int beyond_msb = set_msb << 1;

    return set_msb && !beyond_msb;
}

int int_size_is_32_for_16bit()
{
    int set_msb = 1 << 15 << 15 << 1;
    int beyond_msb = set_msb << 1;

    return set_msb && !beyond_msb;
}

void main()
{
    assert(int_size_is_32());
    assert(int_size_is_32_for_16bit());
}