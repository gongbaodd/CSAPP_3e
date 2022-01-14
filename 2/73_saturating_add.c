#include <stdio.h>
#include <assert.h>
#include <limits.h>

int saturating_add(int x, int y)
{
    int sum = x + y;
    int sig_mask = INT_MIN;
    /*
        if x>0, y>0 but sum<0 then it's a positive overflow
        if x<0, y<0 but sum>- then it's a negative overflow

        INT_MIN = 100...0;
        a&100...0=00..0(FALSE), then a is positive 
    */
    int pos_over = !(x & sig_mask) && !(y & sig_mask) && (sum & sig_mask);
    int neg_over = (x & sig_mask) && (y & sig_mask) && !(sum & sig_mask);

    (pos_over && (sum = INT_MAX)) || neg_over && (sum = INT_MIN);
    return sum;
}

void main()
{
    assert(INT_MAX == saturating_add(INT_MAX, 0x1234));
    assert(INT_MIN == saturating_add(INT_MIN, -0x1234));
    assert(0x11 + 0x22 == saturating_add(0x11, 0x22));
}