#include <stdlib.h>
#include <pthread.h>
#include <stdatomic.h>

#include "../lb+acq+rel.c"

int main()
{
	pthread_t t1, t2;

	if (pthread_create(&t1, NULL, thread_one, NULL))
		abort();
	if (pthread_create(&t2, NULL, thread_two, NULL))
		abort();

	return 0;
}
