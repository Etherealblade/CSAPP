/*
代码无法运行，但是还是敲一次
g++ main.cpp csapp.cpp -o code24 -pthread
*/

#include <cstdio>
#include <cstdio>
#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 
#include "csapp.h"

#define N		2
#define LEN		100

int main()
{
	int status, i;
	pid_t pid;

	/* parent creates N children */
	for (i = 0; i < N; i++)
	{
		if ((pid = Fork()) == 0)
		{
			/* access addr 0, cause fault */
			char* cptr = NULL;
			*cptr = 'd';
		}
	}

	/* Parent reaps N children in no particular order */
	while ((pid = Waitpid(-1, &status, 0)) > 0)
	{
		if (WIFEXITED(status))
		{
			printf("child %d terminated normally with exit status=%d\n",
				pid, WEXITSTATUS(status));
		}
		else if (WIFSIGNALED(status))
		{
			/* print signal that cause process exit */
			char buf[LEN];
			sprintf(buf, "child %d terminated by signal %d",
				pid, WTERMSIG(status));
			psignal(WTERMSIG(status), buf);
		}
		else
			printf("child %d terminated abnormally\n", pid);
	}

	/* 
	the only normal termination is if there are
	no more children 
	*/
	if (errno != ECHILD)
	{
		unix_error("waitpid error");
	}

    // return 0;
	exit(0);
}