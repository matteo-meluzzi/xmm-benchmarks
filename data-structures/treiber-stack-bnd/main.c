#include "my_stack.h"

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

#ifdef CONFIG_STACK_READERS
#define DEFAULT_READERS (CONFIG_STACK_READERS)
#else
#define DEFAULT_READERS 0
#endif

#ifdef CONFIG_STACK_WRITERS
#define DEFAULT_WRITERS (CONFIG_STACK_WRITERS)
#else
#define DEFAULT_WRITERS 2
#endif

#ifdef CONFIG_STACK_RDWR
#define DEFAULT_RDWR (CONFIG_STACK_RDWR)
#else
#define DEFAULT_RDWR 0
#endif

int readers = DEFAULT_READERS, writers = DEFAULT_WRITERS, rdwr = DEFAULT_RDWR;

static mystack_t stack;
static int num_threads;
static pthread_t threads[MAX_THREADS];
static int param[MAX_THREADS];

unsigned int idx1, idx2;
unsigned int a, b;

atomic_int x[3];

int __thread tid;

void set_thread_num(int i)
{
	tid = i;
}

int get_thread_num()
{
	return tid;
}

void *threadR(void *param)
{
	unsigned int val;
	int pid = *((int *)param);

	set_thread_num(pid);

	pop(&stack, POP_R);
exit_thread:
	return NULL;
}

void *threadW(void *param)
{
	unsigned int val;
	int pid = *((int *)param);

	set_thread_num(pid);

	push(&stack, pid);
exit_thread:
	return NULL;
}

void *threadRW(void *param)
{
	unsigned int val;
	int pid = *((int *)param);

	set_thread_num(pid);

	pop(&stack, POP_RW);
	push(&stack, pid);
exit_thread:
	return NULL;
}
