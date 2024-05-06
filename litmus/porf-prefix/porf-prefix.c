atomic_int x;
atomic_int y;
atomic_int z;

void *thread_1(void *unused)
{
    int x_local = atomic_load_explicit(&x, memory_order_relaxed);
    atomic_store_explicit(&z, x_local, memory_order_relaxed);

    atomic_store_explicit(&y, 1, memory_order_relaxed);

    return NULL;
}

void *thread_2(void *unused)
{
    int r2 = atomic_load_explicit(&y, memory_order_relaxed);

    if (atomic_load_explicit(&z, memory_order_relaxed) == 1 && r2) {
        atomic_store_explicit(&x, 42, memory_order_relaxed);
    } else {
        atomic_store_explicit(&x, 1, memory_order_relaxed);
    }


    return NULL;
}