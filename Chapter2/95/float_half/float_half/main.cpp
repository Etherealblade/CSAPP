#include <cstdio>
#include <stdio.h>
#include <assert.h>
#include "float-half.h"

float_bits float_half(float_bits f)
{
	unsigned sig = f >> 31;
	unsigned rest = f & 0x7fffffff;
	unsigned exp = f >> 23 & 0xff;
	unsigned frac = f & 0x7fffff;

	int is_NAN_or_oo = (exp == 0xff);
	if (is_NAN_or_oo)
	{
		return f;
	}

	/*
	round to even, we care about last 2 bits of frac

	00 =>0 just >>1
	01 =>0 (round to even) just >>1
	10 =>1 just >>1
	11 =>1 +1 (round to even) just >>1 and plus 1
	*/

	int addition = (frac & 0x3) == 0x3;

	if (exp == 0)
	{
		frac >>= 1;
		frac += addition;
	}
	else if (exp == 1)
	{
		rest >>= 1;
		rest += addition;
		exp = rest >> 23 & 0xff;
		frac = rest & 0x7fffff;
	}
	else
	{
		exp -= 1;
	}

	return sig << 31 | exp << 23 | frac;
}



int main()
{
    printf("hello from float_half!\n");
    return 0;
}