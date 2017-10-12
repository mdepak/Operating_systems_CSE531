#include<ucontext.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct TCB_type
{
    int thread_id;
    ucontext_t context;
    struct TCB_type *next;
    struct TCB_type *previous;
} TCB_t;


// arguments to init_TCB are
//   1. pointer to the function, to be executed
//   2. pointer to the thread stack
//   3. size of the stack
/*void init_TCB (TCB_t *tcb, void *function, void *stackP, int stack_size)
{
    printf("Initializing the context of the TCB...\n");
    memset(tcb, '\0', sizeof(TCB_t));       // wash, rinse
    if(getcontext(&(tcb->context))== 0) // have to get parent context, else snow forms on hell
    {
      printf("getcontext successful...\n");
    }
    tcb->context.uc_stack.ss_sp = stackP;
    tcb->context.uc_stack.ss_size = (size_t) stack_size;
    //tcb->context.uc_link = &tcb->context;
    makecontext(&(tcb->context), function, 0); // context is now cooked
}*/


void init_TCB (TCB_t *tcb, void *function, void *stackP, int stack_size)
{
    memset(tcb, '\0', sizeof(TCB_t));       // wash, rinse
    getcontext(&tcb->context);              // have to get parent context, else snow forms on hell
    tcb->context.uc_stack.ss_sp = stackP;
    tcb->context.uc_stack.ss_size = (size_t) stack_size;
    makecontext(&tcb->context, function, 0);// context is now cooked
}
