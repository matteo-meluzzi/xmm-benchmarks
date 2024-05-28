#define load(X) atomic_load_explicit(X, memory_order_relaxed)
#define store(X, v) atomic_store_explicit(X, v, memory_order_relaxed)

atomic_int x;
atomic_int y;
atomic_int z;
atomic_int m;

void *thread_1(void *unused)
{
    atomic_store_explicit(&z, 1, memory_order_relaxed);
	return NULL;
}

void *thread_2(void *unused)
{
	int r = atomic_load_explicit(&z, memory_order_relaxed);

    store(&m, 1);
    store(&m, 1);
    
	int s = atomic_load_explicit(&x, memory_order_relaxed);
    if (r == 0 || s == 1) {
	    atomic_store_explicit(&y, 1, memory_order_relaxed);
    }
	return NULL;
}

void *thread_3(void *unused)
{
    load(&m);
	int a = atomic_load_explicit(&y, memory_order_relaxed);
    atomic_store_explicit(&x, a, memory_order_relaxed);
	return NULL;
}
