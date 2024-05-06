#include <stdlib.h>
#include <stdatomic.h>
#include <pthread.h>

#include "../lb+coh+rr+cf.c"

int main()
{
	pthread_t t0, t1, t2, t3;

	if (pthread_create(&t0, NULL, thread_0, NULL))
		abort();

	if (pthread_create(&t1, NULL, thread_3, NULL))
		abort();
	if (pthread_create(&t2, NULL, thread_1, NULL))
		abort();
	if (pthread_create(&t3, NULL, thread_2, NULL))
		abort();

	return 0;
}
