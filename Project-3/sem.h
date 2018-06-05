#include "threads.h"

typedef struct Semaphore
{
	int counter;
	TCB_t *sem_queue;
} Semaphore_t;

Semaphore_t CreateSem(int InputValue)
{
    Semaphore_t *sem;
    int c;
    sem = (Semaphore_t *)(malloc (sizeof(struct Semaphore)));
    sem->counter = InputValue;
		sem->sem_queue = newQueue();
    return *sem;
}

void P(Semaphore_t * sem)
{
	TCB_t* semq;
	TCB_t* rq;
	semq = sem->sem_queue;
	rq = ReadyQ;
    sem->counter--;
    if (sem->counter <0)
    {
			AddQueue(sem->sem_queue,Curr_Thread);
			prev_thread = Curr_Thread;
			Curr_Thread = DelQueue(ReadyQ);
    	swapcontext( &(prev_thread->context), &(Curr_Thread->context));
    }
}

void V(Semaphore_t * sem)
{
    sem->counter++;
    if (sem->counter <= 0)
        {
					AddQueue(ReadyQ, DelQueue(sem->sem_queue));
        }
    yield();
}
