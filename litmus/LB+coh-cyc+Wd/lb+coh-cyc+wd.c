	// Testcase similar to LB+coh-cyc but with a read from
// a distinct location in the second thread and a write
// to this location in a separate thread.
// Behaviour with `r1 = 3`, `r2 = 2` and `r3 = 1` should be still forbidden.

atomic_int x;
atomic_int y;
atomic_int z;

void *thread_1(void *unused)
{
	atomic_store_explicit(&x, 2, memory_order_relaxed);
	int r1 = atomic_load_explicit(&x, memory_order_relaxed);
	if (r1 != 2)
		atomic_store_explicit(&y, 1, memory_order_relaxed);
	return NULL;
}

void *thread_2(void *unused)
{
	atomic_load_explicit(&z, memory_order_relaxed);
	atomic_store_explicit(&x, 1, memory_order_relaxed);
	int r2 = atomic_load_explicit(&x, memory_order_relaxed);
	int r3 = atomic_load_explicit(&y, memory_order_relaxed);
	if (r3)
		atomic_store_explicit(&x, 3, memory_order_relaxed);
	return NULL;
}

void *thread_3(void *unused)
{
	atomic_store_explicit(&z, 1, memory_order_relaxed);
	return NULL;
}

