#include <assert.h>
#include <signal.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "private.h"
#include "uthread.h"

#include "context.c"
#include "queue.c"

Tcb idle;
Tcb current;
Queue *ready_q;

typedef struct uthread_tcb {
	int state;
	void *stack;
	uthread_ctx_t *uctx;

} Tcb;

struct uthread_tcb *uthread_current(void)
{
	return current;
}

void uthread_yield(void)
{
	uthread_ctx_switch(current->uctx, ready_q->head->val);
}

void uthread_exit(void)
{
	queue_dequeue(ready_q, current);
	uthread_ctx_destroy_stack(current->stack);
}

int uthread_create(uthread_func_t func, void *arg)
{
	Tcb *threadBlock = malloc(sizeof (Tcb));

	threadBlock->stack = uthread_ctx_alloc_stack();
	
	if(uthread_ctx_init(threadBlock->uctx, threadBlock->stack, func, arg) == -1)
		return -1;
		
	return 0;
}

int uthread_run(bool preempt, uthread_func_t func, void *arg)
{
	int *ptr;

	if(uthread_create(func, arg) == -1)
		return 1;
	
	idle = malloc(sizeof(Tcb));

	Tcb *initial = malloc(sizeof(Tcb));
	initial->state = 0;
	queue_enqueue(ready_q, initial);

	while(ready_q->count!=0)
	{
		uthead_exit();
		ready_q->count--;
	}
	return 0;
}

void uthread_block(void) {}

void uthread_unblock(struct uthread_tcb *uthread) {}
