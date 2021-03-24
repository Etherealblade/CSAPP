#include <cstdio>
#include <stdio.h>
#include <assert.h>

/*
Mask with least significant n bits set to 1
example: n=6 -> 0x3f, n=17->0x1ffff
assume 1<=n<=w
*/
int lower_one_mask(int n)
{
	int w = sizeof(int) << 3;
	return (unsigned)-1 >> (w - n);
}

int main()
{
	assert(lower_one_mask(6) == 0x3f);
	assert(lower_one_mask(17) == 0x1ffff);
	assert(lower_one_mask(32) == 0xffffffff);
    return 0;
}