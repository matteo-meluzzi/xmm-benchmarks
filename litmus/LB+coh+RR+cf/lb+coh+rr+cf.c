atomic_int x;
atomic_int y;

// The test checks that coherence order is not violated 'globally' on the level of the event structure.
// In particular, it checks that equal writes have same position in 'global' `mo`
// (i.e. relative order of writes can be forced through some equal write in conflicting branch).
// The test checks that in the presence of po-rf cycle,
// W(y,2) cannot be placed earlier in mo order than W(y,1).
// This is because W(y,1) is forced to be `mo`-earlier than equal write W(y,2).
// The relative order of writes can be observed by two reads in a separate thread
// (idea similar to CoRR litmus test).

void *thread_0(void *unused)
{
	atomic_store_explicit(&y, 1, memory_order_relaxed);
	return NULL;
}

void *thread_1(void *unused)
{
	int r1 = atomic_load_explicit(&x, memory_order_relaxed);
	if (!r1) {
		int r2 = atomic_load_explicit(&y, memory_order_relaxed);
		if (r2 == 1)
			atomic_store_explicit(&y, 2, memory_order_relaxed);
	} else {
		atomic_store_explicit(&y, 2, memory_order_relaxed);
	}
	return NULL;
}

void *thread_2(void *unused)
{
	int r2 = atomic_load_explicit(&y, memory_order_relaxed);
	if (r2 == 2)
		atomic_store_explicit(&x, 1, memory_order_relaxed);
	return NULL;
}

void *thread_3(void *unused)
{
	int r3 = atomic_load_explicit(&y, memory_order_relaxed);
	int r4 = atomic_load_explicit(&y, memory_order_relaxed);
	return NULL;
}
