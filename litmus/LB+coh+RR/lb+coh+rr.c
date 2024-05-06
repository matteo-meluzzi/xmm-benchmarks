atomic_int x;
atomic_int y;

// The test asserts that certification does not violate coherence order.
// In more detail, it checks that in the presence of po-rf cycle,
// W(x,2) cannot be placed earlier in mo order than W(x,1).
// The relative order of writes can be observed by two reads in a separate thread
// (idea similar to CoRR litmus test).

void *thread_1(void *unused)
{
	int r1 = atomic_load_explicit(&x, memory_order_relaxed);
	atomic_store_explicit(&x, 2, memory_order_relaxed);
	atomic_store_explicit(&y, 1, memory_order_relaxed);
	return NULL;
}

void *thread_2(void *unused)
{
	int r2 = atomic_load_explicit(&y, memory_order_relaxed);
	if (r2)
		atomic_store_explicit(&x, 1, memory_order_relaxed);
	return NULL;
}

void *thread_3(void *unused)
{
	int r3 = atomic_load_explicit(&x, memory_order_relaxed);
	int r4 = atomic_load_explicit(&x, memory_order_relaxed);
	return NULL;
}
