atomic_int x;
atomic_int y;

atomic_int a;
atomic_int b;

#define load(X) atomic_load_explicit(X, memory_order_relaxed)
#define store(X, v) atomic_store_explicit(X, v, memory_order_relaxed)

void *thread_1(void *unused)
{
	store(&x, load(&a));
	return NULL;
}

void *thread_2(void *unused)
{
	int r1 = load(&x);
    int r2 = load(&y);
    if (r1 == r2) {
        store(&a, 1);
        store(&b, 1);
    }
	return NULL;
}

void *thread_3(void *unused)
{
    store(&y, load(&b));
	return NULL;
}