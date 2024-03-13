atomic_int x;
atomic_int y;

atomic_int z;

void *thread_1(void *unused)
{
	int r = atomic_load_explicit(&x, memory_order_relaxed);

	atomic_store_explicit(&z, 1, memory_order_release);
	atomic_store_explicit(&z, 2, memory_order_release);

	atomic_store_explicit(&y, 1, memory_order_relaxed);
	return NULL;
}

void *thread_2(void *unused)
{
	int r = atomic_load_explicit(&y, memory_order_relaxed);

	atomic_load_explicit(&z, memory_order_acquire);
	atomic_load_explicit(&z, memory_order_acquire);

	atomic_store_explicit(&x, 1, memory_order_relaxed);
	return NULL;
}

