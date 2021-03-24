#include <assert.h>
#include <stdio.h>

unsigned replace_byte(unsigned x, int i, unsigned char b)
{

    if (i < 0)
    {
        printf("error: i is negative\n");
        return x;
    }

    if (i > sizeof(unsigned) - 1)
    {
        printf("error: too big i");
        return x;
    }

    // 1 byte has 8 bits, << 3 means * 8
    unsigned mask = ((unsigned)0xff) << (i << 3);
    unsigned pos_byte = ((unsigned)b) << (i << 3);

    return (x & -mask) | pos_byte;  // error here!
}

int main(int argc, char const *argv[])
{
    unsigned rep_0 = replace_byte(0x12345678, 0, 0xAB);
    unsigned rep_3 = replace_byte(0x12345678, 3, 0xAB);

    printf("rep_0: %X\nrep_3: %X\n", rep_0, rep_3);
    assert(rep_0 == 0x123456AB);
    assert(rep_3 == 0xAB345678);
    return 0;
}
