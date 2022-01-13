#include <stdio.h>
#include <assert.h>

int leftmost_one(unsigned x)
{
    /* 
        generate the mask that all bits are 1 after leftmost 1
        like 0xFF00 => 0xFFFF
        1010>>1=0101; 1010|0101=1111;
        1111>>2=0011; 1111|0011=1111;

        "mask>>1+1" is to remove the 1s, and "mask && 0" deals with the case x=0
        1111>>1=0111; 1111&&1=1;
        0111+0001=1000;
    */

    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    return (x >> 1) + (x && 1);
}

void main()
{
    assert(leftmost_one(0xFF00) == 0x8000);
    assert(leftmost_one(0x6600) == 0x4000);
}