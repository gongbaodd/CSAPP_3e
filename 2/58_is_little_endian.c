#include <stdio.h>
#include <assert.h>

typedef unsigned char *byte_pointer;

int is_little_endian()
{
    int num = 0xff;
    byte_pointer start = (byte_pointer)&num;

    if (start[0] == 0xff)
    {
        return 1;
    }

    return 0;
}

void main()
{
    assert(is_little_endian());
}