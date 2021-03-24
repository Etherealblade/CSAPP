#include <cstdio>
#include "csapp.h"
// P824, explanation is clear 

/* SIGINT handler */
void handler(int sig)
{
	return; /* Catch the signal and return */
}

unsigned int snooze(unsigned int secs) {
	unsigned int rc = sleep(secs);

	printf("Slept for %d of %d secs.\n", secs - rc, secs);
	return rc;

}

int main(int argc, char **argv)
{

	if (argc != 2) {
		fprintf(stderr, "usage: %s <secs>\n", argv[0]);
		exit(0);

	}

	if (signal(SIGINT, handler) == SIG_ERR) /* Install SIGINT */
		unix_error("signal error\n"); /* handler */
	(void)snooze(atoi(argv[1]));
	exit(0);
}