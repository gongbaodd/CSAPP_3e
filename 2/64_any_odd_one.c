#include <stdio.h>
#include <assert.h>

int any_odd_one(unsigned x)
{
    // return 1 when any odd bit of x equals 1
    // should 1: 1010 & 1010 = 1010; !1010 = 0; !!1010 = 1;
    // should 0: 1010 & 0101 = 0000; !0000 = 1; !!0000 = 0;
    return !!(0xAAAAAAAA & x);
}

void main()
{
    assert(any_odd_one(0x2));
    assert(!any_odd_one(0x1));
}