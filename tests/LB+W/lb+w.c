atomic_int x;
atomic_int y;

void *thread_one(void *arg) {
	atomic_load_explicit(&x, memory_order_relaxed);
	atomic_store_explicit(&y, 1, memory_order_relaxed);
	return NULL;
}

void *thread_two(void *arg) {
	atomic_load_explicit(&y, memory_order_relaxed);
	atomic_store_explicit(&x, 1, memory_order_relaxed);
	return NULL;
}

void *thread_three(void *arg) {
	atomic_store_explicit(&y, 2, memory_order_relaxed);
	return NULL;
}

