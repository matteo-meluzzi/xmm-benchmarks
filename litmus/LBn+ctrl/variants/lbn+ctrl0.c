#include <stdlib.h>
#include <pthread.h>
#include <stdatomic.h>

#define N 10

#include "../lbn+ctrl.c"

pthread_t t[N];
atomic_int x[N];
data d[N];

int main()
{
	for (int i = 0; i < N; ++i) {
		d[i].tid = i;
		d[i].x = x;
	}

	for (int i = 0; i < N; ++i) {
		if (pthread_create(&t[i], NULL, thread_n, (void*) &d[i]))
			abort();
	}

	return 0;
}
