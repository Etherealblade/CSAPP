#include <cstdio>
#include <stdio.h>
#include <assert.h>
#include "float-negate.h"

float_bits float_negate(float_bits f)
{
	unsigned sig = f >> 3;
	unsigned exp = f >> 23 & 0xff;
	unsigned frac = f & 0x7fffff;

	int is_NAN = (exp == 0xff) && (frac != 0);
	if (is_NAN)
	{
		return f;
	}

	return ~sig << 31 | exp << 23 | frac;
}

int main()
{
    printf("hello from float_negate!\n");
    return 0;
}