#include <cstdio>
#include <stdio.h>
#include <assert.h>
#include <limits.h>

int divide_power2(int x, int k)
{
	/*
	code from 2.78

	divide by power of 2, -> x/2^k
	assume 0<=k<w-1
	*/
	int is_neg = x & INT_MIN;
	(is_neg && (x = x + (1 << k) - 1));

	int retval = x >> k;
	return retval;
}

int mul3div4(int x)
{
	int mul3 = (x << 1) + x;
	int retval = divide_power2(mul3, 2);
	return retval;
}

int main()
{
	int x = 0x87654321;
	assert(mul3div4(x) == x * 3 / 4);

    return 0;
}