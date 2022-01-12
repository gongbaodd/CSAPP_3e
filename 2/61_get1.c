#include <stdio.h>
#include <assert.h>

int A(int x)
{
    //x all 1s => 1
    // => 0
    return !~x;
}

int B(int x)
{
    // x all 0s => 1
    // => 0
    return !x;
}

int C(int x)
{
    // x low byte all 1 => 1
    // => 0
    return A(x | ~0xff);
}

int D(int x)
{
    // x high byte all 0 => 1
    // => move right 24bit
    return B((x >> ((sizeof(int) - 1) << 3)) & 0xff);
}

void main()
{
    int all_bit_one = ~0;
    int all_bit_zero = 0;
    int low_byte_one = 0x1234 | 0xff;
    int high_byte_zero = 0xfa;

    assert(A(all_bit_one) == 1);
    assert(B(all_bit_one) == 0);
    assert(C(all_bit_one) == 1);
    assert(D(all_bit_one) == 0);

    assert(A(all_bit_zero) == 0);
    assert(B(all_bit_zero) == 1);
    assert(C(all_bit_zero) == 0);
    assert(D(all_bit_zero) == 1);

    assert(A(low_byte_one) == 0);
    assert(B(low_byte_one) == 0);
    assert(C(low_byte_one) == 1);
    assert(D(low_byte_one) == 1);

    assert(A(high_byte_zero) == 0);
    assert(B(high_byte_zero) == 0);
    assert(C(high_byte_zero) == 0);
    assert(D(high_byte_zero) == 1);
}