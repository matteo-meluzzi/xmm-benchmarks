#include <stdlib.h>
#include <stdbool.h>
#include <stdatomic.h>
#include <pthread.h>

#include "../main.c"

int main(int argc, char **argv)
{
	pthread_t W[MAXWRITERS], R[MAXREADERS], RW[MAXRDWR];

	num_threads = readers + writers + rdwr;

	seq_init(&lock);

	int i = 0;
	for (int j = 0; j < writers; j++, i++)
		pthread_create(&W[j], NULL, threadW, NULL);
	for (int j = 0; j < readers; j++, i++)
		pthread_create(&R[j], NULL, threadR, NULL);
	for (int j = 0; j < rdwr; j++, i++)
		pthread_create(&RW[j], NULL, threadRW, NULL);

	for (int j = 0; j < writers; j++)
		pthread_join(W[j], NULL);
	for (int j = 0; j < readers; j++)
		pthread_join(R[j], NULL);
	for (int j = 0; j < rdwr; j++)
		pthread_join(RW[j], NULL);

	return 0;
}
