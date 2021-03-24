#include <cstdio>
#include <stdio.h>
#include <assert.h>

long cread(long* xp)
{
	return (xp ? *xp : 0);
}

long cread_alt(long* xp)
{
	/*
	compile cread_alt may get:
	# xp in %rdi
	cread_alt:

	movl $0, %eax
	testq %rdi, %rdi
	cmovne (%rdi), %rax

	*/
	return (!xp ? 0 : *xp);
}

int main()
{
	long a = 0;
	assert(cread(&a) == cread_alt(&a));
	assert(cread(NULL) == cread_alt(NULL));
    return 0;
}