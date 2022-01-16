#include <stdio.h>
#include <assert.h>
#include <limits.h>

int threeforths(int x)
{
    int is_neg = x & INT_MIN;
    int quarter = x;

    !is_neg && (quarter += 0b11);

    quarter >>= 2;

    return x - quarter;
}

void main()
{
    assert(threeforths(8) == 6);
    assert(threeforths(9) == 6);
    assert(threeforths(10) == 7);
    assert(threeforths(11) == 8);
    assert(threeforths(12) == 9);

    assert(threeforths(-8) == -6);
    assert(threeforths(-9) == -6);
    assert(threeforths(-10) == -7);
    assert(threeforths(-11) == -8);
    assert(threeforths(-12) == -9);
}