#include "sem.h"

typedef struct message
{
    int *msg;
    struct message *next;
    int reply_port;
}message_t;

typedef struct Port
{
Semaphore_t full;
Semaphore_t empty;
Semaphore_t mutex;
message_t *q_head;
}port_t;

// Global - array of ports
port_t ports[100];

void init_port(int port)
{
  ports[port].full = CreateSem(0);
  ports[port].empty = CreateSem(10);
  ports[port].mutex = CreateSem(1);
}

void send(int port, int reply_port, int *msg)
{
  message_t *message = malloc(sizeof(message_t));
  message->msg = msg;
  message->next = '\0';
  message->reply_port = reply_port;

  P(&ports[port].empty);
  P(&ports[port].mutex);
  printf("Added message to the port : %d from port \n", port, reply_port);
  //Add message to the end of Queue
  message_t *qPtr = ports[port].q_head;
  if(qPtr == '\0')
  {
    //printf("message q is null for port %d\n",port);
    ports[port].q_head = message;

  }
  else
    {
      while(qPtr->next!='\0')
      qPtr = qPtr->next;

    qPtr->next = message;
    }

    V(&ports[port].mutex);
    V(&(ports[port].full));
}

void receive(int port, int *reply_port, int **message)
{
  P(&ports[port].full);
  P(&ports[port].mutex);
  message_t *message_ptr = ports[port].q_head;

  ports[port].q_head = ports[port].q_head->next;


  *message = message_ptr->msg;

  //print_array(*message);

  //printf(" In recieve in port %d - reply port is %d\n", port, message_ptr->reply_port);

  *reply_port = message_ptr->reply_port;

  V(&ports[port].mutex);
  V(&(ports[port].empty));
}

 void print_array(int *array)
 {
	 int i;
   printf("=====Printing array====\n");
    for(i=0;i<10; i++)
      {
        printf("%d \t", *(array+i));
      }
    printf("\n=====================================\n");
 }
