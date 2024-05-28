atomic_int x;
atomic_int y;
atomic_int z;
atomic_int a;
atomic_int b;

#define load(X) atomic_load_explicit(X, memory_order_relaxed)
#define store(X, v) atomic_store_explicit(X, v, memory_order_relaxed)

void *thread_1(void *unused)
{
	int r1 = load(&x);
    if (r1 == 0) {
        store(&a, 1);
        store(&y, load(&z));
    } else {
        store(&b, 1);
        store(&y, load(&z));
    }
	return NULL;
}

void *thread_2(void *unused)
{
    if (load(&a) || load(&b)) {
        store(&z, 1);
    }
	return NULL;
}

void *thread_3(void *unused)
{
    store(&x, load(&y));
	return NULL;
}