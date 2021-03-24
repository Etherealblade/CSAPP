#include <cstdio>
#include <stdio.h>
#include <assert.h>
#include <math.h>

float u2f(unsigned x)
{
	return *(float*)&x;
}

float fpwr2(int x)
{
	/* 
	2^x ,result exponent and fraction
	*/
	unsigned exp, frac;
	unsigned u;

	if (x < 2 - pow(2, 7) - 23)
	{
		/* too small, return 0.0 */
		exp = 0;
		frac = 0;
	}
	else if (x < 2 - pow(2, 7))
	{
		/* denormalized result */
		exp = 0;
		frac = 1 << (unsigned)(x - 
			(2 - pow(2, 7) - 23));
	}
	else if (x < pow(2, 7) - 1 + 1)
	{
		/* normalized result */
		exp = pow(2, 7) - 1 + x;
		frac = 0;
	}

	/* pack exp and frac into 32 bits */
	u = exp << 23 | frac;
	/* result as float */

	float retval = u2f(u);
	return retval;
}

int main()
{
	assert(fpwr2(0) == powf(2, 0));
	assert(fpwr2(100) == powf(2, 100));
	assert(fpwr2(-100) == powf(2, -100));
	assert(fpwr2(10000) == powf(2, 10000));
	assert(fpwr2(-10000) == powf(2, -10000));
}