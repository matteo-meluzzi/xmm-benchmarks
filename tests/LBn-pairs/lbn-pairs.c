// Load buffering test with N threads where each pair
// of threads reads/writes from/to distinguished pair of variables.
// An example:
// r1  := [a];  || r2  := [b];  || r3  := [c];  || r4 := [d];
// [b] :=   1;  || [a] :=   1;  || [d] :=   1;  || [c] :=  1;

#define N 10

typedef struct data {
	int tid;
	atomic_int* x;
} data;

void *thread_n(void *arg)
{
	data* d = (data*) arg;
	int tid = d->tid;
	atomic_int* x = d->x;

	int i = (tid & ~1UL) + (tid & 1UL);
	int j = (tid & ~1UL) + (1 - tid & 1UL);

	atomic_load_explicit(&x[i], memory_order_relaxed);
	atomic_store_explicit(&x[j], 1, memory_order_relaxed);

	return NULL;
}

