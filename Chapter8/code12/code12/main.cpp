#include <cstdio>
#include <cstdio>
#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 

void doit()
{
	fork();
	fork();

	printf("hello\n");
	return;	// 猫腻
}

int main()
{
	doit();
	printf("hello\n");
    // return 0;
	exit(0);	// 这就是为什么不用return的原因
}