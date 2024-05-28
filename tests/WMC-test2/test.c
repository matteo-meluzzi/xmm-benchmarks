atomic_int x;
atomic_int y;
atomic_int z;

void *thread_1(void *unused)
{
    atomic_store_explicit(&z, 1, memory_order_relaxed);
	return NULL;
}

void *thread_2(void *unused)
{
	int r = atomic_load_explicit(&z, memory_order_relaxed);
	int s = atomic_load_explicit(&x, memory_order_relaxed);
    if (r == 0 || s == 1) {
	    atomic_store_explicit(&y, 1, memory_order_relaxed);
    }
	return NULL;
}

void *thread_3(void *unused)
{
	int r = atomic_load_explicit(&z, memory_order_relaxed);
	int a = atomic_load_explicit(&y, memory_order_relaxed);
	if (r == 0 || a == 1) {
    	atomic_store_explicit(&x, a, memory_order_relaxed);
	}
	return NULL;
}