#include <cstdio>
#include "csapp.h"

int main(int argc, char **argv)
{
	struct in_addr inaddr;	// addr in network byte order
	uint32_t addr;			// addr in host byte order
	char buf[MAXBUF];		// buf for dotted-decimal string

	if (argc != 2)
	{
		fprintf(stderr, "usage: %s <hex number>\n",
			argv[0]);
		exit(0);
	}
	sscanf(argv[1], "%x", &addr);
	inaddr.s_addr = htonl(addr);

	if (!inet_ntop(AF_INET, &inaddr, buf, MAXBUF))
	{
		unix_error("inet_ntop");
	}
	printf("%s\n", buf);

	exit(0);
}