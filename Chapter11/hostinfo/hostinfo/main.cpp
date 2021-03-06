#include <cstdio>
#include "csapp.h"

int main(int argc, char **argv)
{
	struct addrinfo *p, *listp, hints;
	char buf[MAXLINE];
	int rc, flags;

	if (argc != 2)
	{
		fprintf(stderr, "usage: %s <domain name>\n", 
			argv[0]);
		exit(0);
	}

	// get a list of addrinfo records
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	if ((rc = getaddrinfo(argv[1],
		NULL, &hints, &listp)) != 0)
	{
		fprintf(stderr, "getaddrinfo error: %s\n",
			gai_strerror(rc));
		exit(1);
	}

	// walk the list and display each ip addr
	flags = NI_NUMERICHOST;	
	// display addr string instead of domain name
	for (p = listp; p; p = p->ai_next)
	{
		Getnameinfo(p->ai_addr, p->ai_addrlen,
			buf, MAXLINE, NULL, 0, flags);
		printf("%s\n", buf);
	}

	getchar();
	Freeaddrinfo(listp);

    return 0;
}