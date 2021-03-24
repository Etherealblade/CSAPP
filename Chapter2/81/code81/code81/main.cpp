#include <cstdio>
#include <stdio.h>
#include <assert.h>
/*
此题题意不清
*/
int A(int k)
{
	/* assume 0<=k<w */
	return -1 << k;
}

int B(int k, int j)
{
	/* assume 0<=j,k<w */
	return ~A(k) << j;
}

int main()
{
	assert(A(8) == 0xFFFFFF00);
	assert(B(16, 8) == 0x00FFFF00);

    return 0;
}