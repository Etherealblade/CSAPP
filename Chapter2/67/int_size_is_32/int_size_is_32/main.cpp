#include <cstdio>
#include <stdio.h>
#include <assert.h>

/*
the following func dose not run properly on some machine
*/

/*
int bad_int_size_is_32()
{
	int set_msb = 1 << 31;
	int beyond_msb = 1 << 32;

	return set_msb && !beyond_msb;
}*/

int int_size_is_32()
{
	int set_msb = 1 << 31;
	int beyond_msb = set_msb << 1;

	return set_msb && !beyond_msb;
}

int int_size_is_32_for_16bit()
{
	int set_msb = 1 << 15 << 15 << 1;
	int beyond_msb = set_msb << 1;

	return set_msb && !beyond_msb;
}

int main()
{
	assert(int_size_is_32());
	assert(int_size_is_32_for_16bit());
    return 0;
}