#include <stdlib.h>
#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

#define write_mode memory_order_relaxed
#define read_mode memory_order_relaxed

atomic_char v;

void *thread2(void *arg)
{
	atomic_store_explicit(&v, 'X', write_mode);
	return NULL;
}

void *thread3(void *arg)
{
	atomic_store_explicit(&v, 'Y', write_mode);
	return NULL;
}

int main(void)
{
	pthread_t t1, t2, t3, t4;

	pthread_create(&t1, NULL, thread2, NULL);
	pthread_create(&t2, NULL, thread3, NULL);
	pthread_create(&t3, NULL, thread2, NULL);
	pthread_create(&t4, NULL, thread2, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	pthread_join(t4, NULL);

	int val = atomic_load_explicit(&v, read_mode);
	/* assert(atomic_load_explicit(&v, read_mode) == 'X'); */

	return 0;
}
