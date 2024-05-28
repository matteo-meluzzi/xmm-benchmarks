atomic_int x;
atomic_int y;
atomic_int z;

#define load(X) atomic_load_explicit(X, memory_order_relaxed)
#define store(X, v) atomic_store_explicit(X, v, memory_order_relaxed)

void *thread_1(void *unused)
{
	int a = load(&x);
    if (a == 0) {
        store(&x, 1);
    }
    store(&y, load(&x));
	return NULL;
}

void *thread_2(void *unused)
{
    store(&x, load(&y));
	return NULL;
}

// void *thread_3(void *unused)
// {
//     store(&x, load(&y));
// 	return NULL;
// }