#include <cstdio>
#include "csapp.h"

#define CORRECT

void *pfn_thread(void* vargp);

int main()
{
	/* 
	this code is buggy, because no output
	same as 0823
	*/

	pthread_t tid;
	Pthread_create(&tid, NULL, pfn_thread, NULL);

#ifdef CORRECT
	Pthread_exit(NULL);
#else
	exit(0);
#endif

}

void* pfn_thread(void* vargp)
{
	Sleep(1);	// main thread didn't wait other thread
	printf("hello, world\n");
	return NULL;
}