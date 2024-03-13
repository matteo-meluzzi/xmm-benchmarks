// (Coh-CYC) example from the [Chakraborty-Vafeiadis:POPL19].
// Behaviour with `r1 = 3`, `r2 = 2` and `r3 = 1` should be forbidden,
// since it's impossible to construct required event structure with consistent total modification order.

atomic_int x;
atomic_int y;

void *thread_1(void *unused)
{
	atomic_store_explicit(&x, 2, memory_order_relaxed);
	int r1 = atomic_load_explicit(&x, memory_order_relaxed);
	if (r1 != 2)
		atomic_store_explicit(&y, 1, memory_order_relaxed);
	return NULL;
}

void *thread_2(void *unused)
{
	atomic_store_explicit(&x, 1, memory_order_relaxed);
	int r2 = atomic_load_explicit(&x, memory_order_relaxed);
	int r3 = atomic_load_explicit(&y, memory_order_relaxed);
	if (r3)
		atomic_store_explicit(&x, 3, memory_order_relaxed);
	return NULL;
}
