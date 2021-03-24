#include <cstdio>
#include <stdio.h>
#include <assert.h>
#include "float-f2i.h"

int float_f2i(float_bits f)
{
	/*
	if conversion cause overflow or f is nan, return
	0x80000000
	*/
	unsigned sig = f >> 31;
	unsigned exp = f >> 23 & 0xff;
	unsigned frac = f & 0x7fffff;
	unsigned bias = 0x7f;

	int num;
	unsigned E;
	unsigned M;

	/*
	consider positive numbers

	0 00000000 00000000000000000000000 ===>
	0 01111111 00000000000000000000000

	0<=f<1
	get integer 0

	0 01111111 00000000000000000000000 ===>
	0 (01111111+31) 00000000000000000000000

	1 <= f < 2^31
	integer round to 0

	0 (01111111+31) 00000000000000000000000 ===>
	greater
	2^31 <= f < oo
	return 0x80000000
	*/
	if (exp >= 0 && exp < 0 + bias)
	{
		num = 0;
	}
	else if (exp >= 31 + bias)
	{
		/* number overflow */
		/* or f<0 and (int)f == INT_MIN */
		num = 0x80000000;
	}
	else
	{
		E = exp - bias;
		M = frac | 0x800000;
		if (E > 23)
		{
			num = M << (E - 23);
		}
		else
		{
			/* whether sig is 1 or 0, round to zero */
			num = M >> (23 - E);
		}
	}

	return sig ? -num : num;
}


int main()
{
    printf("hello from float_f2i!\n");
    return 0;
}