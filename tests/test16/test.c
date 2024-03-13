atomic_int x;

void *thread_1(void *unused)
{
	int r1 = atomic_load_explicit(&x, memory_order_relaxed);
	atomic_store_explicit(&x, 1, memory_order_relaxed);
	return NULL;
}

void *thread_2(void *unused)
{
	int r2 = atomic_load_explicit(&x, memory_order_relaxed);
	atomic_store_explicit(&x, 2, memory_order_relaxed);
	return NULL;
}