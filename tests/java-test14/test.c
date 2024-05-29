atomic_int x;
atomic_int y;
atomic_int z;

void *thread_1(void *unused)
{
	int r1 = atomic_load_explicit(&x, memory_order_relaxed);
	if (r1 == 0)
		atomic_store_explicit(&y, 1, memory_order_seq_cst);
	else
		atomic_store_explicit(&z, 1, memory_order_relaxed);
	return NULL;
}

void *thread_2(void *unused)
{
	int r2 = 0, r3 = 0;
	do {
		r2 = atomic_load_explicit(&y, memory_order_seq_cst);
		r3 = atomic_load_explicit(&z, memory_order_relaxed);
	} while (r2 + r3 == 0);
	atomic_store_explicit(&x, 1, memory_order_relaxed);
	return NULL;
}