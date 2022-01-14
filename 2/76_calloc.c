#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

void *yt_calloc(size_t nmemb, size_t size)
{
    void *res = NULL;
    size_t buf_size = nmemb * size;

    !(nmemb ^ (buf_size / size)) && (res = malloc(buf_size)) && memset(res, 0, buf_size);

    return res;
}

void main()
{
    void *p;
    p = yt_calloc(0x1234, 1);
    assert(p != NULL);
    free(p);

    p = yt_calloc(SIZE_MAX, 2);
    assert(p == NULL);
    free(p);
}