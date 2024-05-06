atomic_int x;

void *thread_1(void *unused)
{
	int r1 = 0;
	atomic_compare_exchange_strong_explicit(&x, &r1, 1, memory_order_relaxed, memory_order_relaxed);
	return NULL;
}

void *thread_2(void *unused)
{
	int r2 = 1;
	atomic_compare_exchange_strong_explicit(&x, &r2, 0, memory_order_relaxed, memory_order_relaxed);
	return NULL;
}
