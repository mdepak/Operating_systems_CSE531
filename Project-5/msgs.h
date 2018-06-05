#include "sem.h"

typedef struct message
{
    int msg[10];
    //char *filename;
    struct message *next;
    //int reply_port;
    //int status;
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

void send(int port, message_t *message)
{
//Implement the methods
printf("send message -> to port :: %d\n", port);
printf("message data details- > port : %d , status = %d\n", message->msg[1], message->msg[0]  );

P(&ports[port].empty);

P(&ports[port].mutex);
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
    {
      printf("Port %d : Iterating next pointer for null...\n", port);
      printf("message data - > port : %d , status = %d\n", qPtr->msg[1], qPtr->msg[0]);
      qPtr = qPtr->next;
    }
  qPtr->next = message;
  }

  printf("send message -> message added to port %d\n", port);
  V(&ports[port].mutex);
  V(&(ports[port].full));
}

void receive(int port, message_t **message)
{
  //Implement the methods
  printf("receive message -> from port %d\n", port);
  P(&ports[port].full);
  P(&ports[port].mutex);
  *message = ports[port].q_head;
  //printf("Receive() taken data details - status %d op code %s",ports[port].q_head->msg[0], ports[port].q_head->msg[1]);

  ports[port].q_head = ports[port].q_head->next;

  V(&ports[port].mutex);
  V(&(ports[port].empty));
  printf("receive message -> message taken from port %d\n", port);
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
