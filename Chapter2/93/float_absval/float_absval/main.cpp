#include <cstdio>
#include <stdio.h>
#include <assert.h>
#include "float-absval.h"

float_bits float_absval(float_bits f)
{
	unsigned sig = f >> 31;
	unsigned exp = f >> 23 & 0xff;
	unsigned frac = f & 0x7fffff;

	int is_NAN = (exp == 0xff) && (frac != 0);
	if (is_NAN)
	{
		return f;
	}

	return 0 << 31 | exp << 23 | frac;
}

int main()
{
    printf("hello from float_absval!\n");
    return 0;
}