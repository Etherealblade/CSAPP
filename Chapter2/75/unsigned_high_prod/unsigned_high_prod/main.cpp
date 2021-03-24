#include <cstdio>
#include <stdio.h>
#include <assert.h>
#include <inttypes.h>

int signed_high_prod(int x, int y)
{
	int64_t mul = (int64_t)x*y;
	return mul >> 32;
}

unsigned unsigned_high_prod(unsigned x, unsigned y)
{
	/* Todo calculations*/
	int sig_x = x >> 31;
	int sig_y = y >> 31;
	int signed_prod = signed_high_prod(x, y);
	
	unsigned retval = signed_prod + x * sig_y +
		y * sig_x;
	return retval;
}

unsigned another_unsigned_high_prod(unsigned x, unsigned y)
{
	/*
	a theorically correct version to 
	test unsigned_high_prod func
	*/
	uint64_t mul = (uint64_t)x*y;
	unsigned retval = mul >> 32;
	return retval;
}

int main()
{
	unsigned x = 0x12345678;
	unsigned y = 0xffffffff;

	assert(another_unsigned_high_prod(x, y) ==
		unsigned_high_prod(x, y));

    return 0;
}