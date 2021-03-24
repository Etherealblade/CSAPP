#include <assert.h>
#include <stdio.h>

typedef unsigned char *byte_pointer;

int is_little_endian()
{
    int test_num = 0x78ff;
    byte_pointer byte_start = (byte_pointer)&test_num;

    if (byte_start[0] == 0xff && byte_start[1] == 0x78)
    {
        return 1;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    assert(is_little_endian());
    printf("is_little_endian: %d\n", is_little_endian());
    return 0;
}