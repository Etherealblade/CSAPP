#include <cstdio>
#include "csapp.h"

#define WRITE_LIMIT	100000
#define PEOPLE		4

static int readtimes;
static int writetimes;	
static int readcnt;
static int reader_first;
/* 
pay attention static int reader_first,
if a reader is waiting when writing, reader first 
next round 
*/
sem_t mutex, w;	// ’‚¡©semaphore ≤√¥”√Õæ£ø

void *reader(void *vargp)
{
	while (1)
	{
		P(&mutex);
		readcnt++;
		if (readcnt == 1)
		{
			P(&w);
		}
		V(&mutex);

		// critical section
		readtimes++;
		reader_first = 0;
		// critical section

		P(&mutex);
		readcnt--;
		if (readcnt==0)
		{
			V(&w);
		}
		V(&mutex);
	}
}

void *write(void* vargp)
{
	while (1)
	{
		if (reader_first == 1)
		{
			continue;
		}
		P(&w);	

		// critical section
		writetimes++;
		if (writetimes == WRITE_LIMIT)
		{
			printf("read/write: %d/%d\n",
				readtimes, writetimes);
			exit(0);
		}
		// critical section

		// if a reader is waiting,reader first next roud
		if (readcnt == 1)
		{
			reader_first = 1;
		}
		V(&w);
	}
}

void init(void)
{
	readcnt = 0;
	readtimes = 0;
	writetimes = 0;
	reader_first = 0;
	Sem_init(&w, 0, 1);
	Sem_init(&mutex, 0, 1);
}

int main()
{
	int i;
	pthread_t tid;

	init();

	for (i = 0; i < PEOPLE; i++)
	{
		if (i % 2 == 0)
		{
			Pthread_create(&tid, NULL, reader, NULL);
		}
		else
		{
			Pthread_create(&tid, NULL, write, NULL);
		}
	}

	getchar();
	Pthread_exit(NULL);

	exit(0);
}