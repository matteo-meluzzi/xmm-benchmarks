atomic_int x;
atomic_int y;
atomic_int z;

void *thread_one(void *arg)
{
	int r1 = atomic_load_explicit(&x, memory_order_relaxed);
	if (!r1) {
		atomic_store_explicit(&y, 1, memory_order_relaxed);
	} else {
		atomic_store_explicit(&z, 1, memory_order_relaxed);
		atomic_store_explicit(&y, 1, memory_order_relaxed);
	}
	return NULL;
}

void *thread_two(void *arg)
{
	int r2 = atomic_load_explicit(&y, memory_order_relaxed);
	int r3 = atomic_load_explicit(&z, memory_order_relaxed);
	if (r2) {
		atomic_store_explicit(&x, 1, memory_order_relaxed);
//		if (r3) {
//			assert(false);
//		}
	}
	return NULL;
}
