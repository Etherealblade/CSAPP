#include <cstdio>
#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 

int counter = 1;

int main()
{
	if (fork()==0)	// child
	{
		counter--;
		exit(0);
	}
	else
	{
		wait(NULL);
		printf("counter = %d\n", ++counter);
	}

    // return 0;
	exit(0);
}