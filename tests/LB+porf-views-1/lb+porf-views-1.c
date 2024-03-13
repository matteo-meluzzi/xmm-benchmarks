atomic_int x;
atomic_int y;
atomic_int z;

// This load buffering test is crafted specifically to test
// the behavior of porf views in the presence of the porf cycles.
// In particular it asserts that the algorithm properly cuts
// the porf views when it handles porf-backward revisits.
//
// In more detail, we have two threads with load buffering pattern on `x,y` variables.
// The first thread has fake control dependency via `if` statement.
// In the `then` branch it also performs additional writes to `x`
// (it is used only to occupy some space, to guarantee that the second thread
//  will exceed the size of the first thread after the certification).
// In the `else` branch there is an additional read from `z`.
// The second thread, after reading from `x` and writing to `y`, also writes to `z`.
// The latter write should generate a revisit option for the read in the first thread.
// However, if the porf view of the write to `z` was not cut properly,
// it will see beyond the existing events of the first thread.

void *thread_one(void *arg)
{
	int r1 = atomic_load_explicit(&x, memory_order_relaxed);
	if (!r1) {
		atomic_store_explicit(&x, 2, memory_order_relaxed);
		atomic_store_explicit(&x, 3, memory_order_relaxed);
		atomic_store_explicit(&x, 4, memory_order_relaxed);
		atomic_store_explicit(&y, 1, memory_order_relaxed);
	} else {
		atomic_store_explicit(&y, 1, memory_order_relaxed);
		atomic_load_explicit(&z, memory_order_relaxed);
	}
	return NULL;
}

void *thread_two(void *arg)
{
	int r3 = atomic_load_explicit(&y, memory_order_relaxed);
	atomic_store_explicit(&x, r3, memory_order_relaxed);
	atomic_store_explicit(&z, 1, memory_order_relaxed);
	return NULL;
}
