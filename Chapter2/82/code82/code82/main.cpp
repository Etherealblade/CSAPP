#include <cstdio>
#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include "lib/random.h"

int A(int x, int y)
{
	/*broken when x is INT_MIN */
	return (x > y) == (-x > -y);
}

int B(int x, int y)
{
	/*
	right
	((x+y)<<4)+y-x
	=>
	x<<4-x+y<<4+y
	=>
	x*16-x+y*16+y
	whether overflow or not, =>
	x*15+y*17

	*/

	return((x + y << 4)) + y - x
		== 17 * y + 15 * x;
}

int C(int x, int y)
{
	/*
	right
	~x+~y+1 =>
	~x+1+~y+1-1 =>
	-x + -y - 1 =>
	-(x+y)-1 =>
	~(x+y)+1-1 =>
	~(x+y)

	*/
	return ~x + ~y + 1 == ~(x + y);
}

int D(int x, int y)
{
	/*
	right

	(ux - uy) == -(unsigned) (y - x)
	=>
	-(ux - uy) == (unsigned) (y - x)
	=>
	(ux - uy) == (unsigned) (x - y)

	*/
	unsigned ux = (unsigned)x;
	unsigned uy = (unsigned)y;
	return (ux - uy) == -(unsigned)(y - x);
}

int E(int x, int y)
{
	/*

	right
	x >> 2 << 2
	= >
	& ~0x3
	= >
	x - num(00 / 01 / 10 / 11)
	= >
	((x >> 2) << 2) <= x

	*/
	return((x >> 2) << 2) <= x;
}


int main()
{
	init_seed();
	int x = random_int();
	int y = random_int();
	assert(!A(INT_MIN, 0));
	assert(B(x, y));
	assert(C(x, y));
	assert(D(x, y));
	assert(E(x, y));

	return 0;
}