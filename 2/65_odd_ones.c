#include <stdio.h>
#include <assert.h>

int odd_ones(unsigned x)
{
    // return 1 when x contains an odd number of 1s
    // 0101>>2=0001; 0101^0001=0100; 0100>>1=0010; 0100^0010=0000; 0000&0001=0;
    // 1000>>2=0010; 1000^0010=1010; 1010>>1=0101; 1010^0101=1111; 1111&0001=1;
    // if there're odd 1s meaning there's one more 1 in pairs

    x ^= x >> 16;
    x ^= x >> 8;
    x ^= x >> 4;
    x ^= x >> 2;
    x ^= x >> 1;
    x &= 0x1;
    return x;
}

void main()
{
    assert(odd_ones(0x10101011));
    assert(!odd_ones(0x10101010));
}