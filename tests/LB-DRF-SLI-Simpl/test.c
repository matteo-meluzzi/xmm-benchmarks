atomic_int x;
atomic_int y;
atomic_int z;

#define load(X) atomic_load_explicit(X, memory_order_relaxed)
#define store(X, v) atomic_store_explicit(X, v, memory_order_relaxed)

void *thread_1(void *unused)
{
	store(&z, 1);
	return NULL;
}

void *thread_2(void *unused)
{
    int r = load(&z);
    int s = load(&x);
    if (r == 0 || (r == 1 && s == 1)) {
        store(&y, 1);
    }
	return NULL;
}

void *thread_3(void *unused)
{
    store(&x, load(&y));
	return NULL;
}