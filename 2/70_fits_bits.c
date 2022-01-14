#include <stdio.h>
#include <assert.h>

int fits_bits(int x, int n)
{
    /*
        assume w = 8; n = 3
        if x > 0:
            0b00000010 is ok
            0b00001000 is not
            0b00000100 neither
        if x < 0:
            0b11111100 is ok
            0b11011110 is not
    */
    int w = sizeof(int) << 3;
    int offset = w - n;
    return (x << offset >> offset) == x;
}

void main()
{
    assert(!fits_bits(0xFF, 8));
    assert(!fits_bits(~0xFF, 8));

    assert(fits_bits(0b10, 3));
    assert(!fits_bits(0b1010, 3));
    assert(!fits_bits(0b0110, 3));

    assert(fits_bits(~0b11, 3));
    assert(!fits_bits(0b0100011, 3));
    assert(!fits_bits(~0b111, 3));
}