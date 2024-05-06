atomic_int x;
atomic_int y;
atomic_int z;

// Variant of `LB-DRF` test case to which "Speculative Load Introduction" and "Load/Load Reordering"
// transformations have been applied.
// It checks for soundness of load/load reordering,
// i.e. the test case should have the same number of outcomes as DRF-SLI.

void *thread_1(void *unused)
{
        int r2 = atomic_load_explicit(&x, memory_order_relaxed);
	int r1 = atomic_load_explicit(&z, memory_order_relaxed);
	if (!r1 || r2) {
		atomic_store_explicit(&y, 1, memory_order_relaxed);
	}
	return NULL;
}

void *thread_2(void *unused)
{
	int r3 = atomic_load_explicit(&y, memory_order_relaxed);
	if (r3)
		atomic_store_explicit(&x, 1, memory_order_relaxed);
	return NULL;
}

void *thread_3(void *unused)
{
	atomic_store_explicit(&z, 1, memory_order_relaxed);
	return NULL;
}