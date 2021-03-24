#include <cstdio>
#include <stdio.h>
#include <assert.h>

/*
Do rotate left shift. assume 0<=n<w
example when x=0x12345678 and w = 32:
n = 4 -> 0x23456781, n = 20 -> 0x67812345
*/
unsigned rotate_left(unsigned x, int n)
{
	int w = sizeof(unsigned) << 3;
	/* pay attention when n==0 */
	printf("x << n: %x", x << n);
	printf("x >> (w - n - 1) >> 1: %x",
		x >> (w - n - 1) >> 1);
	//unsigned retval = x << n | x >> (w - n - 1) >> 1;
	unsigned retval = x << n | x >> (w - n);
	// ��Ϊn=0�����Բ�д��x >> (w - n)?

	return retval;
}

int main()
{
	assert(rotate_left(0x12345678, 4) == 0x23456781);
	assert(rotate_left(0x12345678, 20) == 0x67812345);
	rotate_left(0x12345678, 0);	// �����������line18�ɵ���ȷ���
	return 0;
}