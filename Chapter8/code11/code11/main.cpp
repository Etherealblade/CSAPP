#include <cstdio>
#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 


int main()
{
	int i;
	for ( i = 0; i < 2; i++)
	{
		fork();
	}

	printf("hello\n");
	exit(0);
}