// Load buffering test with N threads and a load buffering pattern spanning through all threads.
// An example:
// r1  := [a];  || r2  := [b];  || r3  := [c];  || r4 := [d];
// [b] :=   1;  || [c] :=   1;  || [d] :=   1;  || [a] :=  1;

typedef struct data {
	int tid;
	atomic_int* x;
} data;

void *thread_n(void *arg)
{
	data* d = (data*) arg;
	int tid = d->tid;
	atomic_int* x = d->x;

	int i = tid % N;
	int j = (tid + 1) % N;

	atomic_load_explicit(&x[i], memory_order_relaxed);
	atomic_store_explicit(&x[j], 1, memory_order_relaxed);

	return NULL;
}

