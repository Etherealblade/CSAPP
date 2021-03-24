#include <cstdio>
#include "csapp.h"

char *tfgets(char *s, int size, FILE *stream)
{
	fd_set read_set;
	FD_ZERO(&read_set);
	FD_SET(STDIN_FILENO, &read_set);

	struct timeval timeout;
	timeout.tv_sec = 5;
	timeout.tv_usec = 0;

	Select(1, &read_set, NULL, NULL, &timeout);
	// key is last param of 

	if (FD_ISSET(STDIN_FILENO, &read_set))
	{
		return fgets(s, size, stream);
	}
	else
	{
		return NULL;
	}
}


int main()
{
	char buf[MAXLINE];

	if (tfgets(buf, MAXLINE, stdin) == NULL)
		printf("BOOM!\n");
	else
		printf("%s", buf);

	getchar();
	return 0;
}