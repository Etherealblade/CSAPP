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
	return;	// è��
}

int main()
{
	doit();
	printf("hello\n");
    // return 0;
	exit(0);	// �����Ϊʲô����return��ԭ��
}