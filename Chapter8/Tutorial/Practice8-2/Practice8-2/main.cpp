#include <cstdio>
#include "csapp.h"

int main()
{
	int a = 9;

	if (Fork() == 0)	// Child
	{ 
		printf("P1: a=%d\n", --a);
		// exit(0)	// differ from Figure8-15 due to this line
	}
	
	// Parent 
	printf("P2: a=%d\n", ++a);
	exit(0);
}