atomic_int x;
atomic_int y;
atomic_int u;
atomic_int v;

void *thread_one(void *arg) {
	int a = atomic_load_explicit(&x, memory_order_relaxed);
    if (!a) {
	    atomic_store_explicit(&y, 1, memory_order_relaxed);
    } else {
		a = atomic_load_explicit(&u, memory_order_relaxed);
		atomic_store_explicit(&v, 1, memory_order_relaxed);
		
		atomic_store_explicit(&y, a, memory_order_relaxed);
    }
	return NULL;
}

void *thread_two(void *arg) {
	atomic_store_explicit(&x, atomic_load_explicit(&y, memory_order_relaxed), memory_order_relaxed);
	return NULL;
}

void *thread_three(void *arg) {
	atomic_store_explicit(&u, 1, memory_order_relaxed);
	int b = atomic_load_explicit(&v, memory_order_relaxed);
	return NULL;
}

