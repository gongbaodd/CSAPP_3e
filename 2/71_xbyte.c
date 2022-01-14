#include <stdio.h>
#include <assert.h>

typedef unsigned packed_t;

int xbyte(packed_t word, int bytenum)
{
    // return (word >> (bytenum << 3)) & 0xFF; // cannot extract negative number

    int max_bytenum = 3;
    int left_shift_bits = (max_bytenum - bytenum) << 3;
    int right_shift_bits = max_bytenum << 3;

    return (int)word << left_shift_bits >> right_shift_bits;
}

void main()
{
    assert(xbyte(0x00112233, 0) == 0x33);
    assert(xbyte(0x00112233, 1) == 0x22);
    assert(xbyte(0x00112233, 2) == 0x11);
    assert(xbyte(0x00112233, 3) == 0x00);

    assert(xbyte(0xAABBCCDD, 0) == 0xFFFFFFDD);
    assert(xbyte(0xAABBCCDD, 1) == 0xFFFFFFCC);
    assert(xbyte(0xAABBCCDD, 2) == 0xFFFFFFBB);
    assert(xbyte(0xAABBCCDD, 3) == 0xFFFFFFAA);
}