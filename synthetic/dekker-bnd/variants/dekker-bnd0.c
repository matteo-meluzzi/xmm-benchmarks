#include <stdlib.h>
#include <pthread.h>
#include <stdatomic.h>
#include <assert.h>

/* Testcase from Threader's distribution. For details see:
   http://www.model.in.tum.de/~popeea/research/threader
*/

#define BND 3

/* boolean flags */
atomic_int flag1 = ATOMIC_VAR_INIT(0);
atomic_int flag2 = ATOMIC_VAR_INIT(0);

atomic_int turn; // integer variable to hold the ID of the thread whose turn is it

int x; // boolean variable to test mutual exclusion

void *thr1(void *unused)
{
	atomic_store_explicit(&flag1, 1, memory_order_relaxed);
	atomic_thread_fence(memory_order_seq_cst);

	for (int i = 0u; i <= BND; i++) {
		if (i == BND)
			return NULL;
		if (atomic_load_explicit(&flag2, memory_order_relaxed) < 1)
			break;

		if (atomic_load_explicit(&turn, memory_order_relaxed) != 0) {
			atomic_store_explicit(&flag1, 0, memory_order_relaxed);
			for (int i = 0u; i <= BND; i++) {
				if (i == BND)
					return NULL;
				if (atomic_load_explicit(&turn, memory_order_relaxed) == 0)
					break;
			}
			atomic_store_explicit(&flag1, 1, memory_order_relaxed);
			atomic_thread_fence(memory_order_seq_cst);
		}
	}
	atomic_thread_fence(memory_order_acquire);

	/* begin: critical section */
	x = 0;
	assert(x <= 0);
	/* end: critical section */

	atomic_store_explicit(&turn, 1, memory_order_relaxed);
	atomic_thread_fence(memory_order_release);
	atomic_store_explicit(&flag1, 0, memory_order_relaxed);
	return NULL;
}

void *thr2(void *unused)
{
	atomic_store_explicit(&flag2, 1, memory_order_relaxed);
	atomic_thread_fence(memory_order_seq_cst);

	for (int i = 0u; i <= BND; i++) {
		if (i == BND)
			return NULL;
		if (atomic_load_explicit(&flag1, memory_order_relaxed) < 1)
			break;

		if (atomic_load_explicit(&turn, memory_order_relaxed) != 1) {
			atomic_store_explicit(&flag2, 0, memory_order_relaxed);
			for (int i = 0u; i <= BND; i++) {
				if (i == BND)
					return NULL;
				if (atomic_load_explicit(&turn, memory_order_relaxed) == 1)
					break;
			}
			atomic_store_explicit(&flag2, 1, memory_order_relaxed);
			atomic_thread_fence(memory_order_seq_cst);
		}
	}
	atomic_thread_fence(memory_order_acquire);

	/* begin: critical section */
	x = 1;
	assert(x >= 1);
	/* end: critical section */

	atomic_store_explicit(&turn, 0, memory_order_relaxed);
	atomic_thread_fence(memory_order_release);
	atomic_store_explicit(&flag2, 0, memory_order_relaxed);
	return NULL;
}

int main()
{
	pthread_t t1, t2;

	pthread_create(&t1, NULL, thr1, NULL);
	pthread_create(&t2, NULL, thr2, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	return 0;
}
