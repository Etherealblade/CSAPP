#include <cstdio>
#include <stdio.h>
#include <assert.h>
#include <limits.h>

int saturating_add(int x, int y)
{
	/*
	if x>0,y>0 but sum<0,it's a positive overflow
	if x<0,y<0 but sum>=0,it's a negative overflow
	*/
	int sum = x + y;
	int sig_mask = INT_MIN;
	int pos_over = !(x&sig_mask) && !(y&sig_mask) &&
		(sum&sig_mask);
	int neg_over = (x&sig_mask) && (y&sig_mask) &&
		!(sum&sig_mask);

	(pos_over && (sum = INT_MAX) ||
		neg_over && (sum = INT_MIN));
	// 这句代码意义何在？

	return sum;
}

int main()
{
	assert(INT_MAX == saturating_add(INT_MAX, 0x1234));
	assert(INT_MIN == saturating_add(INT_MIN, -0x1234));
	assert(0x11 + 0x22 == saturating_add(0x11, 0x22));

    return 0;
}