#include <cstdio>
#include <stdio.h>
#include <assert.h>

int odd_ones(unsigned x)
{
	x ^= x >> 16;
	x ^= x >> 8;
	x ^= x >> 4;
	x ^= x >> 2;
	x ^= x >> 1;
	x &= 0x1;
	return x;
}

int main()
{
	assert(odd_ones(0x10101011));
	printf("odd_ones(0x10101011) :%d\n",
		odd_ones(0x10101011));
	assert(!odd_ones(0x01010101));
    return 0;
}