#include <cstdio>
#include "csapp.h"

void *thread(void *vargp);

int main()
{
	pthread_t tid;
	Pthread_create(&tid, NULL, thread, NULL);
	Pthread_join(tid, NULL);	// wait for peer thread to terminate
	exit(0);
}

void *thread(void *vargp) /* Thread routine */
{
	printf("Hello, world!\n");
	return NULL;
}

