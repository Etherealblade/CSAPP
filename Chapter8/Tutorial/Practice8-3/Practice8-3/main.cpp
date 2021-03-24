#include <cstdio>
#include "csapp.h"

// P823, solution
int main()
{
	if (Fork() == 0) 
	{
		printf("9\n"); 
		fflush(stdout);

	}
	else 
	{
		// 这个格局比较好理解
		printf("0\n"); 
		fflush(stdout);
		waitpid(-1, NULL, 0);

	}
	printf("3\n"); 
	fflush(stdout);
	printf("6\n"); 
	exit(0);
}