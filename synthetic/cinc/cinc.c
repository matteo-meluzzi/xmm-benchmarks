atomic_int x;
atomic_int y;
atomic_int z;

void *thread_n(void *unused)
{
	atomic_fetch_add_explicit(&x, 1, memory_order_relaxed);
	atomic_fetch_add_explicit(&y, 1, memory_order_relaxed);
	atomic_fetch_add_explicit(&z, 1, memory_order_relaxed);
	return NULL;
}
