#include <cstdio>
#include <stdio.h>
#include <assert.h>
#include "float-twice.h"

float_bits float_twice(float_bits f)
{
	unsigned sig = f >> 31;
	unsigned exp = f >> 23 & 0xff;
	unsigned frac = f & 0x7fffff;
	int is_NAN_or_oo = (exp == 0xff);
	if (is_NAN_or_oo)
	{
		return f;
	}

	if (exp==0)
	{
		/* denormalized */
		frac <<= 1;
	}
	else if (exp == 0xff - 1)
	{
		/* twice to oo */
		exp = 0xff;
		frac = 0;
	}
	else
	{
		/* normalized */
		exp += 1;
	}

	return sig << 31 | exp << 23 | frac;
}

int main()
{
    printf("hello from float_twice!\n");
    return 0;
}