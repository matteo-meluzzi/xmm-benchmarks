// Load buffering test with N threads and a load buffering pattern spanning through all threads;
// additionally all threads except the first one have a real data dependency between load/store.
// An example:
// r1  := [a];  || r2  := [b];  || r3  := [c];  || r4 := [d];
// [b] :=   1;  || [c] :=  r2;  || [d] :=  r3;  || [a] := r4;

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

	if (i == 0) {
		atomic_load_explicit(&x[i], memory_order_relaxed);
		atomic_store_explicit(&x[j], 1, memory_order_relaxed);
	} else {
		int ri = atomic_load_explicit(&x[i], memory_order_relaxed);
		atomic_store_explicit(&x[j], ri, memory_order_relaxed);
	}

	return NULL;
}