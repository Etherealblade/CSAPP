#include <cstdio>
#include <stdio.h>
#include <assert.h>
#include <limits.h>

int tsub_ok(int x, int y)
{
	int res = 1;
	(y == INT_MIN) && (res = 0);	// 意义何在？
	// 这里居然是改变res的值为0

	int sub = x - y;	// sub=0-0x80000000=0x80000000，卧槽
	int pos_over = x > 0 && y < 0 && sub < 0;
	int neg_over = x < 0 && y>0 && sub > 0;

	res = res && !(pos_over || neg_over);

	return res;
}

int main()
{
	assert(!tsub_ok(0x00, INT_MIN));
	assert(tsub_ok(0x00, 0x00));
    return 0;
}