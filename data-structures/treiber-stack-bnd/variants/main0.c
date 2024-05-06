#include <stdlib.h>
#include <stdbool.h>
#include <stdatomic.h>
#include <pthread.h>
#include <assert.h>

#include "../main.c"

int main()
{
	pthread_t W[MAXWRITERS], R[MAXREADERS], RW[MAXRDWR];

	num_threads = readers + writers + rdwr;
	for (int j = 0; j < num_threads; j++)
		param[j] = j;

	init_stack(&stack, num_threads);

	int i = 0;
	for (int j = 0; j < writers; j++, i++)
		pthread_create(&W[j], NULL, threadW, &param[i]);
	for (int j = 0; j < readers; j++, i++)
		pthread_create(&R[j], NULL, threadR, &param[i]);
	for (int j = 0; j < rdwr; j++, i++)
		pthread_create(&RW[j], NULL, threadRW, &param[i]);

	for (int j = 0; j < writers; j++)
		pthread_join(W[j], NULL);
	for (int j = 0; j < readers; j++)
		pthread_join(R[j], NULL);
	for (int j = 0; j < rdwr; j++)
		pthread_join(RW[j], NULL);

	return 0;
}
