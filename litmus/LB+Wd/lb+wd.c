atomic_int x;
atomic_int y;
atomic_int z;

// Load buffering test with one of the threads performing an additional load
// from the distinct location (not participating to the po-rf cycle)
// and the third thread performing a write to this location.
// The test asserts that the revisit generated by the third thread
// will not cause any trouble and that the po-rf cycle will be correctly restored.

void *thread_one(void *arg) {
	atomic_load_explicit(&x, memory_order_relaxed);
	atomic_store_explicit(&y, 1, memory_order_relaxed);
	return NULL;
}

void *thread_two(void *arg) {
	int r1 = atomic_load_explicit(&y, memory_order_relaxed);
	if (!r1) {
		atomic_store_explicit(&x, 1, memory_order_relaxed);
	} else {
		atomic_load_explicit(&z, memory_order_relaxed);
		atomic_store_explicit(&x, 1, memory_order_relaxed);
	}
	return NULL;
}

void *thread_three(void *arg) {
	atomic_store_explicit(&z, 1, memory_order_relaxed);
	return NULL;
}

