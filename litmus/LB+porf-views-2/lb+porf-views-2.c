atomic_int x;
atomic_int y;
atomic_int z;

// This load buffering test is crafted specifically to test
// the behavior of porf views in the presence of the porf cycles.
// In particular it asserts that the algorithm updates
// the porf views after closing the cycle, so that all events
// in the cycle `see` each other.
//
// In more detail, we have two threads with load buffering pattern on `x,y` variables.
// The first thread has fake control dependency via `if` statement.
// In the `else` branch it also performs additional write to `x`
// (it is used only to occupy some space, to guarantee that the second thread
//  will not see subsequent events if the porf view is not updated).
// and then reads from `z`.
// The second thread, after reading from `x` and writing to `y`, also writes to `z`.
// The latter write should generate a revisit option for the read in the first thread.
// More importantly, the algorithm should detect that it is porf-backward revisit.
// If the po-rf views are not updated correctly, it might not detect that and
// it will lead to out-of-thin-air reads.

void *thread_one(void *arg)
{
	int r1 = atomic_load_explicit(&x, memory_order_relaxed);
	if (!r1) {
		atomic_store_explicit(&y, 1, memory_order_relaxed);
	} else {
		atomic_store_explicit(&x, 2, memory_order_relaxed);
		int r2 = atomic_load_explicit(&z, memory_order_relaxed);
		atomic_store_explicit(&y, 1 + r2, memory_order_relaxed);
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
