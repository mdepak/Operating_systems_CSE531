#include "TCB.h"
#include<stdlib.h>

#define handle_error(msg) \
           do { perror(msg); exit(EXIT_FAILURE); } while (0)

TCB_t* NewItem(void *function, void *SP, int stack_size)
{
    TCB_t *tcb = (TCB_t *) malloc(sizeof(TCB_t));
    init_TCB(tcb, function, SP, stack_size);
    return tcb;
}

TCB_t* newQueue()
{
  TCB_t *dummy_head = malloc(sizeof(TCB_t));
  if(dummy_head == NULL)
  {
    printf("Memory allocation error\n");
  }
  //don't need to initialize the tcb for the dummy header
  dummy_head->thread_id = -1;
  dummy_head->next = dummy_head;
  dummy_head->previous = dummy_head;
  return dummy_head;
}

void AddQueue(TCB_t *head, TCB_t *item)
{
  printf("Adding the tcb block to the queue\n");
  TCB_t *last_tcb = head->previous;
  item->next = last_tcb->next;
  item->previous = last_tcb;
  last_tcb->next = item;
  head->previous = item;
}

TCB_t* DelQueue(TCB_t *head)
{
  printf("Removing the first element from the Queue\n");
  TCB_t *tcb;
  if(head->next!= head)
  {
    tcb = head->next;
    printf("Remove the tcb block with thread id %d\n", tcb->thread_id);
    head->next = tcb->next;
    head->next->previous = head;
  }
  else
  {
      printf("Queue is empty...\n");
      handle_error("ReadyQ is empty");
  }
  printf("Removed the first element from the Queue\n");
  return tcb;
}
