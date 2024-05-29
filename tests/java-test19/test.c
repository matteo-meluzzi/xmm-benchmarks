atomic_int x;
atomic_int y;

void *thread_1(void *unused)
{
	int r1 = atomic_load_explicit(&x, memory_order_relaxed);
	if (r1 != 42)
		atomic_store_explicit(&x, 42, memory_order_relaxed);
	return NULL;
}

void *thread_2(void *unused)
{
	int r2 = atomic_load_explicit(&x, memory_order_relaxed);
	atomic_store_explicit(&y, r2, memory_order_relaxed);
	return NULL;
}

void *thread_3(void *unused)
{
	int r3 = atomic_load_explicit(&y, memory_order_relaxed);
	atomic_store_explicit(&x, r3, memory_order_relaxed);
	return NULL;
}