#include <cstdio>
#include "csapp.h"

#define DEFAULT	4

void *pfn_thread(void *vargp);


int main(int argc, char* argv[])
{
	int N;
	if (argc > 2)
	{
		unix_error("too many param");
	}

	else if (argc == 2)
	{
		N = atoi(argv[1]);
	}
	else
	{
		N = DEFAULT;
	}

	int i;
	pthread_t tid;
	for (i = 0; i < N; i++)
	{
		pthread_create(&tid, NULL, 
			pfn_thread, NULL);
	}
	pthread_exit(NULL);

	getchar();
    return 0;
}

void *pfn_thread(void *vargp)
{
	printf("hello, world\n");
}