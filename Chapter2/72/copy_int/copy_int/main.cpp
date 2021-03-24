#include <cstdio>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

void error_demo(int val, void* buff, int maxbytes)
{
	/*
	sizeof(val) returns type size_t, it usually is a
	kind of unsigned type. calc maxbytes-sizeof(val)
	always get size_t typte value, and it always >=0
	*/
	if (maxbytes - sizeof(val) >= 0)
	{
		memcpy(buff, (void *)&val, sizeof(val));
		// ÓÀÔ¶ÕýÈ·
	}
}

void copy_int(int val, void* buf, int maxbytes)
{
	/*
	compare two signed number, avoid someone set
	maxbytes a negative value
	*/
	if (maxbytes >= (int)sizeof(val))
	{
		memcpy(buf, (void*)&val, sizeof(val));
	}
}

int main()
{
	int maxbytes = sizeof(int) * 10;
	void* buf = malloc(maxbytes);
	int val;

	val = 0x12345678;
	copy_int(val, buf, maxbytes);
	assert(*(int*)buf == val);

	val = 0xaabbccdd;
	copy_int(val, buf, 0);
	assert(*(int*)buf != val);
	error_demo(val, buf, 0);
	assert(*(int*)buf == val);

    return 0;
}