#include <cstdio>
#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 

int main()
{
	int x = 3;
	if (fork() != 0)
	{
		printf("x=%d\n", ++x);
	}

	printf("x=%d\n", --x);
	// return 0;
	exit(0);
}