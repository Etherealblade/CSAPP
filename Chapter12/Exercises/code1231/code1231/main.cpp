#include <cstdio>
#include "csapp.h"

sigjmp_buf buf;

void sigchild_handler(int sig)
{
	siglongjmp(buf, 1);
}

char* tfgets(char* s, int size, FILE* stream)
{
	if (Fork() == 0)
	{
		Sleep(5);
		exit(0);
	}

	switch (sigsetjmp(buf, 1))
	{
	case 0:
		Signal(SIGCHLD, sigchild_handler);
		return fgets(s, size, stream);

	case 1:
		return NULL;
	}
}


int main(int argc, char* argv[])
{
	char buf[MAXLINE];

	if (tfgets(buf, MAXLINE, stdin) == NULL)
	{
		printf("boom!\n");
	}
	else
	{
		printf("%s", buf);
	}

	getchar();
    return 0;
}