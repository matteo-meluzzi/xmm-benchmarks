atomic_int a;
atomic_int b;

atomic_int x;
atomic_int y;

void *thread_1(void *unused)
{
	int r0 = atomic_load_explicit(&x, memory_order_seq_cst);
	int r1;
	if (r0 == 1)
		r1 = atomic_load_explicit(&a, memory_order_relaxed);
	else
		r1 = 0;
	if (r1 == 0)
		atomic_store_explicit(&y, 1, memory_order_seq_cst);
	else
		atomic_store_explicit(&b, 1, memory_order_relaxed);
	return NULL;
}

void *thread_2(void *unused)
{
	int r2 = 0, r3 = 0;
	do {
		r2 = atomic_load_explicit(&y, memory_order_seq_cst);
		r3 = atomic_load_explicit(&b, memory_order_relaxed);
	} while (r2 + r3 == 0);
	atomic_store_explicit(&a, 1, memory_order_relaxed);
	return NULL;
}

void *thread_3(void *unused)
{
	atomic_store_explicit(&x, 1, memory_order_seq_cst);
	return NULL;
}