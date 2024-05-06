#ifndef BND
# define BND 3
#endif

typedef struct seqlock {
	/* Sequence for reader consistency check */
	atomic_int _seq;
	/* It needs to be atomic to avoid data races */
	atomic_int _data;
} seqlock_t;

void seq_init(seqlock_t *seq)
{
	atomic_init(&seq->_seq, 0);
	atomic_init(&seq->_data, 0);
	return;
}

int seq_read(seqlock_t *seq)
{
	for (int i = 0u; i <= BND; i++) {
		if (i == BND)
			return -1;

		int old_seq = atomic_load_explicit(&seq->_seq, memory_order_acquire); // acquire
		if (old_seq % 2 == 1)
			continue;

		int res = atomic_load_explicit(&seq->_data, memory_order_acquire); // acquire
		if (atomic_load_explicit(&seq->_seq, memory_order_relaxed) == old_seq) { // relaxed
			return res;
		}
	}
	return -42;
}

void seq_write(seqlock_t *seq, int new_data)
{
	for (int i = 0u; i <= BND; i++) {
		if (i == BND)
			return;

		// This might be a relaxed too
		int old_seq = atomic_load_explicit(&seq->_seq, memory_order_acquire); // acquire
		if (old_seq % 2 == 1)
			continue; // Retry

		// Should be relaxed!!!
		if (atomic_compare_exchange_strong_explicit(&seq->_seq, &old_seq, old_seq + 1,
							    memory_order_relaxed,
							    memory_order_relaxed)) // relaxed
			break;
	}

	// Update the data
	atomic_store_explicit(&seq->_data, new_data, memory_order_release); // release

	atomic_fetch_add_explicit(&seq->_seq, 1, memory_order_release); // release
}

#ifdef MAKE_ALL_SC
# define release memory_order_seq_cst
# define acquire memory_order_seq_cst
# define relaxed memory_order_seq_cst
#else
# define release memory_order_release
# define acquire memory_order_acquire
# define relaxed memory_order_relaxed
#endif

#define MAXREADERS 3
#define MAXWRITERS 3
#define MAXRDWR 3

#define MAX_THREADS (MAXREADERS + MAXWRITERS + MAXRDWR + 1)

#ifdef CONFIG_LOCK_READERS
#define DEFAULT_READERS (CONFIG_LOCK_READERS)
#else
#define DEFAULT_READERS 0
#endif

#ifdef CONFIG_LOCK_WRITERS
#define DEFAULT_WRITERS (CONFIG_LOCK_WRITERS)
#else
#define DEFAULT_WRITERS 2
#endif

#ifdef CONFIG_LOCK_RDWR
#define DEFAULT_RDWR (CONFIG_LOCK_RDWR)
#else
#define DEFAULT_RDWR 0
#endif

int readers = DEFAULT_READERS, writers = DEFAULT_WRITERS, rdwr = DEFAULT_RDWR;

static int num_threads;
static pthread_t threads[MAX_THREADS];

seqlock_t lock;

void *threadR(void *obj)
{
	seq_read(&lock);
	return NULL;
}

void *threadW(void *obj)
{
	seq_write(&lock, 1);
	return NULL;
}

void *threadRW(void *obj)
{
	seq_read(&lock);
	seq_write(&lock, 2);
	return NULL;
}
