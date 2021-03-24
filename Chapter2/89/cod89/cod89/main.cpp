#include <cstdio>
#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include "lib/random.h"

int A(int x, double dx)
{
	/*
	right
	most important thing is that all double number
	come from ints
	*/
	return (float)x == (float)dx;
}

int B(int x, double dx, int y, double dy)
{
	/*
	wrong when y is INT_MIN
	*/
	return dx - dy == (double)(x - y);
}

int C(double dx, double dy, double dz)
{
	/* right */
	return (dx + dy) + dz == dx + (dy + dz);
}

int D(double dx, double dy, double dz)
{
	/*
	wrong 
	fixme i don't know what conditions cause false
	*/
	return (dx*dy)*dz == dx * (dy*dz);
}

int E(double dx, double dz)
{
	/* wrong when dx!=0 dz==0 */
	return dx / dz == dz / dz;
}


int main()
{
	init_seed();

	int x = random_int();
	int y = random_int();
	int z = random_int();
	double dx = (double)x;
	double dy = (double)y;
	double dz = (double)z;

	printf("%x %x %x\n", x, y, z);

	assert(A(x, dx));
	assert(!B(0, (double)(int)0, INT_MIN, 
		(double)(int)INT_MIN));
	assert(C(dx, dy, dz));
	/* magic number, brute force attack */
	assert(!D((double)(int)0x64e73387, (double)(int)0xd31cb264, 
		(double)(int)0xd22f1fcd));
	assert(!E(dx, (double)(int)0));

    return 0;
}