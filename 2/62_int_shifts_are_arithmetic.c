#include <stdio.h>
#include <assert.h>

int int_shifts_are_arithmetic()
{
    int num = -1;
    return !(num ^ (num >> 1));
}

void main()
{
    assert(int_shifts_are_arithmetic());
}