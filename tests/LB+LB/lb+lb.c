atomic_int a;
atomic_int b;
atomic_int c;
atomic_int d;

void *thread_one(void *arg) {
	atomic_load_explicit(&a, memory_order_relaxed);
	atomic_load_explicit(&b, memory_order_relaxed);
	atomic_store_explicit(&c, 1, memory_order_relaxed);
	atomic_store_explicit(&d, 1, memory_order_relaxed);
	return NULL;
}

void *thread_two(void *arg) {
	int r1 = atomic_load_explicit(&d, memory_order_relaxed);
	if (r1) {
		atomic_store_explicit(&a, 1, memory_order_relaxed);
	}
	return NULL;
}

void *thread_three(void *arg) {
	int r2 = atomic_load_explicit(&c, memory_order_relaxed);
	if (r2) {
		atomic_store_explicit(&b, 1, memory_order_relaxed);
	}
	return NULL;
}

