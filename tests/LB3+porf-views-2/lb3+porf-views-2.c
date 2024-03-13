atomic_int x;
atomic_int y;
atomic_int z;
atomic_int w;

// Same test as LB+porf-views-2 but with more threads participating in the po-rf cycle

void *thread_one(void *arg)
{
	int r1 = atomic_load_explicit(&x, memory_order_relaxed);
	if (!r1) {
		atomic_store_explicit(&y, 1, memory_order_relaxed);
	} else {
		atomic_store_explicit(&x, 2, memory_order_relaxed);
		int r2 = atomic_load_explicit(&z, memory_order_relaxed);
		atomic_store_explicit(&y, 1 + r2, memory_order_relaxed);
	}
	return NULL;
}

void *thread_two(void *arg)
{
	int r3 = atomic_load_explicit(&y, memory_order_relaxed);
	atomic_store_explicit(&w, r3, memory_order_relaxed);
	return NULL;
}

void *thread_three(void *arg)
{
	int r4 = atomic_load_explicit(&w, memory_order_relaxed);
	atomic_store_explicit(&x, r4, memory_order_relaxed);
	atomic_store_explicit(&z, 1, memory_order_relaxed);
	return NULL;
}
