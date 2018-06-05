// (c) Partha Dasgupta 2009
// permission to use and distribute granted.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "msgs.h"


//Team mates:
/*
Anudeep Sanepalli -   1210442230
Deepak Mahudeswaran - 1213175078
*/

void server()
{
  int server_port = 10;
  printf("\nserver started..\n");
  init_port(server_port);
  while(1)
  {
    int *message = '\0';
    int reply_port;
    receive(server_port, &reply_port, &message);

    printf("Server : Received message from client with port: %d\n", reply_port);
    print_array(message);

    // Do some operation with the message
    sleep(1);

    printf("Server : Sending message from server with port %d to client with port %d\n", server_port, reply_port);
    send(reply_port, server_port, message);
  }
}


void client1()
{
  printf("\nclient1 started..\n");
  int i;
  int client_port = 1;
  int server_port = 10;
  int *message = (int) malloc(10 *sizeof(int));
  for(i = 0;i<10; i++)
  message[i] = 1;

  init_port(client_port);

  while(1)
  {
    //Modify message and sent to server_port
    message[0] = message[0] + 1;

    printf("Client 1 : Sending message to server with port :%d from client with port:%d\n",server_port, client_port);
    send(server_port, client_port, message);

    sleep(1);

    //printf("Client 1 : Waiting to receive message in the client with port:%d\n", client_port);
    receive(client_port, &server_port, &message);
    printf("Client 1 : Received message from server with port: %d\n in client with port:%d\n",server_port, client_port);
  }
}

void client2()
{
  printf("client2 started..\n");
  int i;
  int client_port = 2;
  int server_port = 10;
  int *message = (int) malloc(10 *sizeof(int));
  for(i = 0;i<10; i++)
  message[i] = 1;

  init_port(client_port);

  while(1)
  {
    //Modify message and sen(t to server_port
    message[9] = message[9] + 1;
    printf("Client 2 : Sending message to server with port :%d from client with port:%d\n",server_port, client_port);
    send(server_port, client_port, message);


    sleep(1);
    //printf("Client 2 : Waiting to receive message in the client with port:%d\n", client_port);
    receive(client_port, &server_port, &message);
    printf("Client 2 : Received message from server with port: %d\n in client with port:%d\n",server_port, client_port);
  }
}

void client3()
{
  printf("client3 started..\n");
  int i;
  int client_port = 3;
  int server_port = 10;
  int *message = (int) malloc(10 *sizeof(int));
  for(i = 0;i<10; i++)
  message[i] = 1;

  init_port(client_port);

  while(1)
  {
    //Modify message and sen(t to server_port
    message[1] = message[1] + 1;
    printf("Client 3 : Sending message to server with port :%d from client with port:%d\n",server_port, client_port);
    send(server_port, client_port, message);


    sleep(1);
    //printf("Client 3 : Waiting to receive message in the client with port:%d\n", client_port);
    receive(client_port, &server_port, &message);
    printf("Client 3 : Received message from server with port: %d\n in client with port:%d\n",server_port, client_port);
  }
}


void client4()
{
  printf("client4 started..\n");
  int i;
  int client_port = 4;
  int server_port = 10;
  int *message = (int) malloc(10 *sizeof(int));
  for(i = 0;i<10; i++)
  message[i] = 1;

  init_port(client_port);

  while(1)
  {
    //Modify message and sen(t to server_port
    message[2] = message[2] + 1;
    printf("Client 4 : Sending message to server with port :%d from client with port:%d\n",server_port, client_port);
    send(server_port, client_port, message);


    sleep(1);
    //printf("Client 4 : Waiting to receive message in the client with port:%d\n", client_port);
    receive(client_port, &server_port, &message);
    printf("Client 4 : Received message from server with port: %d\n in client with port:%d\n",server_port, client_port);
  }
}

void client5()
{
  printf("client5 started..\n");
  int i;
  int client_port = 5;
  int server_port = 10;
  int *message = (int) malloc(10 *sizeof(int));
  for(i = 0;i<10; i++)
  message[i] = 1;

  init_port(client_port);

  while(1)
  {
    //Modify message and sen(t to server_port
    message[3] = message[3] + 1;
    printf("Client 5 : Sending message to server with port :%d from client with port:%d\n",server_port, client_port);
    send(server_port, client_port, message);


    sleep(1);
    //printf("Client 5 : Waiting to receive message in the client with port:%d\n", client_port);
    receive(client_port, &server_port, &message);
    printf("Client 5 : Received message from server with port: %d\n in client with port:%d\n",server_port, client_port);
  }
}

void client6()
{
  printf("client6 started..\n");
  int i;
  int client_port = 6;
  int server_port = 10;
  int *message = (int) malloc(10 *sizeof(int));
  for(i = 0;i<10; i++)
  message[i] = 1;

  init_port(client_port);

  while(1)
  {
    //Modify message and sen(t to server_port
    message[4] = message[4] + 1;
    printf("Client 6 : Sending message to server with port :%d from client with port:%d\n",server_port, client_port);
    send(server_port, client_port, message);


    sleep(1);
    //printf("Client 6 : Waiting to receive message in the client with port:%d\n", client_port);
    receive(client_port, &server_port, &message);
    printf("Client 6 : Received message from server with port: %d\n in client with port:%d\n",server_port, client_port);
  }
}

void client7()
{
  printf("client7 started..\n");
  int i;
  int client_port = 7;
  int server_port = 10;
  int *message = (int) malloc(10 *sizeof(int));
  for(i = 0;i<10; i++)
  message[i] = 1;

  init_port(client_port);

  while(1)
  {
    //Modify message and sen(t to server_port
    message[5] = message[5] + 1;
    printf("Client 7 : Sending message to server with port :%d from client with port:%d\n",server_port, client_port);
    send(server_port, client_port, message);


    sleep(1);
    //printf("Client 7 : Waiting to receive message in the client with port:%d\n", client_port);
    receive(client_port, &server_port, &message);
    printf("Client 7 : Received message from server with port: %d\n in client with port:%d\n",server_port, client_port);
  }
}

void client8()
{
  printf("client8 started..\n");
  int i;
  int client_port = 8;
  int server_port = 10;
  int *message = (int) malloc(10 *sizeof(int));
  for(i = 0;i<10; i++)
  message[i] = 1;

  init_port(client_port);

  while(1)
  {
    //Modify message and sen(t to server_port
    message[6] = message[6] + 1;
    printf("Client 8 : Sending message to server with port :%d from client with port:%d\n",server_port, client_port);
    send(server_port, client_port, message);


    sleep(1);
    //printf("Client 8 : Waiting to receive message in the client with port:%d\n", client_port);
    receive(client_port, &server_port, &message);
    printf("Client 8 : Received message from server with port: %d\n in client with port:%d\n",server_port, client_port);
  }
}

void client9()
{
  printf("client9 started..\n");
  int i;
  int client_port = 9;
  int server_port = 10;
  int *message = (int) malloc(10 *sizeof(int));
  for(i = 0;i<10; i++)
  message[i] = 1;

  init_port(client_port);

  while(1)
  {
    //Modify message and sen(t to server_port
    message[7] = message[7] + 1;
    printf("Client 9 : Sending message to server with port :%d from client with port:%d\n",server_port, client_port);
    send(server_port, client_port, message);


    sleep(1);
    //printf("Client 9 : Waiting to receive message in the client with port:%d\n", client_port);
    receive(client_port, &server_port, &message);
    printf("Client 9 : Received message from server with port: %d\n in client with port:%d\n",server_port, client_port);
  }
}

void client10()
{
  printf("client10 started..\n");
  int i;
  int client_port = 11;
  int server_port = 10;
  int *message = (int) malloc(10 *sizeof(int));
  for(i = 0;i<10; i++)
  message[i] = 1;

  init_port(client_port);

  while(1)
  {
    //Modify message and sen(t to server_port
    message[8] = message[8] + 1;
    printf("Client 10 : Sending message to server with port :%d from client with port:%d\n",server_port, client_port);
    send(server_port, client_port, message);


    sleep(1);
    //printf("Client 10 : Waiting to receive message in the client with port:%d\n", client_port);
    receive(client_port, &server_port, &message);
    printf("Client 10 : Received message from server with port: %d\n in client with port:%d\n",server_port, client_port);
  }
}

void client11()
{
  printf("client11 started..\n");
  int i;
  int client_port = 12;
  int server_port = 10;
  int *message = (int) malloc(11 *sizeof(int));
  for(i = 0;i<10; i++)
  message[i] = 1;

  init_port(client_port);

  while(1)
  {
    //Modify message and sen(t to server_port
    message[10] = message[10] + 1;
    printf("Client 11 : Sending message to server with port :%d from client with port:%d\n",server_port, client_port);
    send(server_port, client_port, message);


    sleep(1);
    //printf("Client 12 : Waiting to receive message in the client with port:%d\n", client_port);
    receive(client_port, &server_port, &message);
    printf("Client 12 : Received message from server with port: %d\n in client with port:%d\n",server_port, client_port);
  }
}

//-------------------------------------------------------

int main()
{
  init_readyQueue();;

  start_thread(server);

  start_thread(client1);
  start_thread(client2);
  start_thread(client3);
  start_thread(client4);
  start_thread(client5);
  start_thread(client6);
  start_thread(client7);
  start_thread(client8);
  start_thread(client9);
  start_thread(client10);
  start_thread(client11);
  run();
}
