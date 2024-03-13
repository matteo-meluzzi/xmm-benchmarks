atomic_int x;
atomic_int y;
atomic_int z;

void *thread_1(void *unused)
{
	int r1 = atomic_load_explicit(&z, memory_order_relaxed);
	int r2 = atomic_load_explicit(&x, memory_order_relaxed);
	atomic_store_explicit(&y, r2, memory_order_relaxed);
	return NULL;
}

void *thread_2(void *unused)
{
	int r3 = atomic_load_explicit(&y, memory_order_relaxed);
	atomic_store_explicit(&z, r3, memory_order_relaxed);
	atomic_store_explicit(&x, 1, memory_order_relaxed);
	return NULL;
}
