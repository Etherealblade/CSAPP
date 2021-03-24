/*
将4个有符号字节封装成一个32位unsigned
xbyte(packet_t word, int bytenum)
这里第二个参数bytenum是什么意思？
*/

#include <cstdio>
#include <stdio.h>
#include <assert.h>

typedef unsigned packet_t;

int error_demo(packet_t word, int bytenum)
{
	// This func can't extract a negative 
	// byte number from word
	int retval = (word >> (bytenum << 3)) & 0xff;
	return retval;
}

int xbyte(packet_t word, int bytenum)
{
	/*
	pay attention when byte we want is negative

	assume sizeof(unsigned) is 4
	first shift left 8*(4-1-bytenum)
	then arithmetic shift right 8*(4-1) reserve 
	significant bit
	*/
	int size = sizeof(unsigned);
	int shift_left_val = (size - 1 - bytenum) << 3;
	int shift_right_val = (size - 1) << 3;
	int retval = (int)word << shift_left_val >> shift_right_val;

	return retval;
}

int main()
{
	assert(xbyte(0xAABBCCDD, 1) == 0xFFFFFFCC);
	assert(xbyte(0x00112233, 2) == 0x11);
	if (error_demo(0xAABBCCDD, 1) != 0xFFFFFFCC)
	{
		printf("error_demo\n");
	}
    return 0;
}