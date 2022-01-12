#include <stdio.h>
#include <assert.h>

unsigned srl(unsigned x, int k)
{
    // Perform shift arithmetically
    unsigned xsra = (int)x >> k;

    int w = sizeof(int) << 3;      // 32
    int mask = (int)-1 << (w - k); // F0000000(k=4)

    return xsra & ~mask;
    // remove all the high k bit 1s
}

unsigned sra(int x, int k)
{
    // Perform shift logically
    unsigned xsrl = (unsigned)x >> k;

    int w = sizeof(int) << 3;
    int mask = (int)-1 << (w - k);

    int m = 1 << (w - 1);
    mask &= !(x & m) - 1;

    return xsrl | mask;
    /*
    x = 1xxx
        x&m = 100...0
        !(x&m) = 0...0
        !(x&m) - 1 = 1111..1
        mask&(!(x&m) - 1) = 1111...10000..0 //set all the high 0s to 1s
    x = 0xxx
        x&m = 0...0
        !(x&m) = 0...1
        !(x&m) - 1 = 0....0
        mask&(!(x&m) - 1) = 0....0 // unchanged
    */
}

void main()
{
    unsigned test_unsigned = 0x12345678;
    int test_int = 0x12345678;

    assert(srl(test_unsigned, 4) == test_unsigned >> 4);
    assert(sra(test_int, 4) == test_int >> 4);

    test_unsigned = 0x87654321;
    test_int = 0x87654321;

    assert(srl(test_unsigned, 4) == test_unsigned >> 4);
    assert(sra(test_int, 4) == test_int >> 4);
}