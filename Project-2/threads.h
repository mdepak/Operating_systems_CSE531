#include "q.h"
#define STACK_SIZE (8192)

TCB_t* Curr_Thread;
TCB_t* ReadyQ;
int count = 0;

void init_readyQueue()
{
  ReadyQ = newQueue();
}

void start_thread(void (*function)(void))
{
  void *stack = malloc(8192);
  TCB_t *newTCB = NewItem(function, stack, 8192);
  newTCB->thread_id = ++count;
  AddQueue(ReadyQ, newTCB);
}

void run()
{
  printf("Running thread from the ReadyQ\n");
  Curr_Thread = DelQueue(ReadyQ);

  //Curr_Thread = ReadyQ->next;
  printf("Current thread to be run - %d \n", Curr_Thread->thread_id);
  ucontext_t parent;     // get a place to store the main context, for faking
  getcontext(&parent);   // magic sauce
  printf("Got the parent context\n");
  swapcontext(&parent, &(Curr_Thread->context));  // start the first thread
}

void yield()
{
  printf("Running the next thread from the ReadyQ\n");
  TCB_t* prev_thread;
  AddQueue(ReadyQ, Curr_Thread);
  prev_thread = Curr_Thread;
  Curr_Thread = DelQueue(ReadyQ);
  //  swap the context, from Prev_Thread to the thread pointed to Curr_Thread
  swapcontext(&(prev_thread->context), &(Curr_Thread->context));
}


void printQueue()
{
  printf("Printing the running Queue\n");
  TCB_t *temp;
  while(temp->next!=ReadyQ)
  {
    printf("TCB block with thread id : %d\n", temp->thread_id);
  }
}
