#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

#define write_mode memory_order_relaxed
#define read_mode memory_order_relaxed

#define USAGE "./reorder <param1> <param2>\n"

static int iSet = 2;
static int iCheck = 2;

static atomic_int a = 0;
static atomic_int b = 0;

void *setThread(void *param)
{
	atomic_store_explicit(&a, 1, write_mode);
	atomic_store_explicit(&b, -1, write_mode);
	return NULL;
}

void *checkThread(void *param)
{
	if (! ((atomic_load_explicit(&a, read_mode) == 0 && atomic_load_explicit(&b, read_mode) == 0) ||
	       (atomic_load_explicit(&a, read_mode) == 1 && atomic_load_explicit(&b, read_mode) == -1))) {
		/* fprintf(stderr, "Bug found!\n"); */
		/* assert(0); */
	}
	return NULL;
}

int main(int argc, char *argv[])
{
	pthread_t setPool[iSet];
	pthread_t checkPool[iCheck];

	for (int i = 0; i < iSet; i++) {
		if (pthread_create(&setPool[i], NULL, &setThread, NULL))
			abort();
	}

	for (int i = 0; i < iCheck; i++) {
		if (pthread_create(&checkPool[i], NULL, &checkThread,  NULL))
			abort();
	}

	for (int i = 0; i < iSet; i++) {
		if (pthread_join(setPool[i], NULL))
			abort();
	}

	for (int i = 0; i < iCheck; i++) {
		if (pthread_join(checkPool[i], NULL))
			abort();
	}

	return 0;
}
