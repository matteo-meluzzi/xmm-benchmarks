#include "barrier.h"

#ifndef NUMREADERS
# define NUMREADERS 4
#endif

DEFINE_BARRIER(barr, NUMREADERS + 1);

int var = 0;

void *threadW(void *unused)
{
	var = 42;
	wait(&barr, W1);
exit_thread:
	return NULL;
}

void *threadR(void *unused)
{
	wait(&barr, W2);
	int data = var;
exit_thread:
	return NULL;
}
