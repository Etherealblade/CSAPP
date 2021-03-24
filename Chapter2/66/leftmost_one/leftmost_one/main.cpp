#include <cstdio>
#include <stdio.h>
#include <assert.h>

/*
Generate mask indicating leftmost 1 in x. assume w=32
for example, 0xff00->0x8000,and 0x6000->0x4000
if x=0, the return 0
*/
int leftmost_one(unsigned x)
{
	/*
	first, generate a mask that all bits after leftmost
	one are 1
	e.g. 0xff00->0xffff, and 0x06000->0x7fff
	*/
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;

	/*
	then, do(mask >>1)+(mask &&1), in which mask &&1
	deals with case x=0, reserver leftmost bit one
	that's we want
	*/
	return (x >> 1) + (x && 1);
}

int main()
{
	assert(leftmost_one(0xff00) == 0x8000);
	assert(leftmost_one(0x6000) == 0x4000);
	assert(leftmost_one(0x0) == 0x0);
	assert(leftmost_one(0x80000000) == 0x80000000);

	return 0;
}