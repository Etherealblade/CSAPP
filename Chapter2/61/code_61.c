#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int A(int x)
{
    return !~x;
}

int B(int x)
{
    return !x;
}

int C(int x)
{
    return A(x | ~0xff);
}

int D(int x)
{
    return B((x >> ((sizeof(int) - 1) << 3)) & 0xff);
    // can't debug!
}

int main(int argc, char const *argv[])
{
    int all_bit_one = ~0;
    int all_bit_zero = 0;

    assert(A(all_bit_one));
    assert(!B(all_bit_one));
    assert(C(all_bit_one));
    assert(!D(all_bit_one));

    assert(!A(all_bit_zero));
    assert(B(all_bit_zero));
    assert(!C(all_bit_zero));
    assert(D(all_bit_zero));

    // test magic number 0x1234ff
    assert(!A(0x1234ff));
    assert(!B(0x1234ff));
    assert(C(0x1234ff));
    assert(D(0x1234ff));

    assert(!A(0x1234));
    assert(!B(0x1234));
    assert(!C(0x1234));
    assert(D(0x1234));

    printf("a: %8d\n", A(0x1234));
    printf("b: %8d\n", B(0x1234));
    printf("c: %8d\n", C(0x1234));
    printf("d: %8d\n", D(0x1234));

    return 0;
}
