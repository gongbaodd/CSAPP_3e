// replace_byte(0x12345678, 2, 0xAB) ---> 0x12AB5678
// replace_byte(0x12345678, 0, 0xAB) ---> 0x123456AB

#include <stdio.h>
#include <assert.h>

unsigned replace_byte(unsigned x, int i, unsigned char b)
{
    if (i < 0)
    {
        printf("Need a positive i");
        return x;
    }

    if (i > sizeof(unsigned) - 1)
    {
        printf("i is too big");
        return x;
    }

    // if i == 0, mask is 0x000000FF(0xFF*0*8)
    // if i == 2, mask is 0x00FF0000(0xFF*2*8)
    unsigned mask = ((unsigned)0xFF) << (i << 3);
    unsigned pos_byte = ((unsigned)b) << (i << 3);

    return (x & ~mask) | pos_byte;
}

void main()
{
    unsigned rep_0 = replace_byte(0x12345678, 0, 0xAB);
    unsigned rep_2 = replace_byte(0x12345678, 2, 0xAB);

    assert(rep_0 == 0x123456AB);
    assert(rep_2 == 0x12AB5678);
}