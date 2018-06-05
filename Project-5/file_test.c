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

int client_port_number = 0;
Semaphore_t mutex;
char clientFileNames[99][100];

int packToInt(char *a) {
	int b = 0;
	int i = 0;
	b = a[i++];
	while(i <= 3) {
		b = b << 8;
		b = b | a[i++];
	}
	return b;
}

void unPackToChar(int n, char *res) {
	char d,c,b,a;
	a = (n & (255 << 24)) >> 24;
	b = (n & (255 << 16)) >> 16;
	c = (n & (255 << 8)) >> 8;
	d = n & 255;
	res[0] = a;
	res[1] = b;
	res[2] = c;
	res[3] = d;
}


void server()
{
  int server_port = 0;
  printf("\nserver started..\n");
  init_port(server_port);
  FILE *fptr;

  char serverFileNames[99][25];

  int clientConnectionCount = 0;
  //char filename[25];

  while(1)
  {
    message_t *message = '\0';
    int reply_port;

    printf("Server waiting to receive message ...\n");
    receive(server_port, &message);
    //reply_port = message -> reply_port;
      reply_port = message->msg[1];

    printf("Server received message from client %d...\n", reply_port);

    //strcpy(filename, message->filename);


    //int op_code = message->status;
    int op_code = message->msg[0];
    if(op_code ==1)
    {
      char buff[8];
      //strcpy(buff, message->msg);
      int len = 0;
      char fname[37] = "\0";

      for(int i=2; i<10; i++) {
        char str[4] = "\0";
        unPackToChar(message->msg[i], str);
        strcat(fname, str);
        strcat(fname, "\0");
      }

      printf("Server message : %s\n", buff);

      message_t *message = malloc(sizeof(message_t));
      message->next = '\0';
      message->msg[1] = server_port;

      printf("Server: init request from client %d\n",reply_port);
      if(strlen(fname) >15)
      {
        //File name limit is not proper - so handle it
        //message->status = 400;
        message->msg[0] = 400;
        printf("Server : File name limit exceeded\n");
        send(reply_port, message);
      }
      else if(clientConnectionCount >=3)
      {
        //busy
        //message->status = 300;
        message->msg[0] = 300;
        printf("Server : busy...\n");
        send(reply_port, message);
      }
      else
      {
        strcat(fname, ".server");
        strcpy(serverFileNames[reply_port-1],fname);
        printf("Implement connection : file name : %s\n", fname);
        fptr = fopen(fname,"a");
        fclose(fptr);
        //fwrite(buff, 1, len * sizeof(char), fptr);
        message->msg[0] = 200;
        clientConnectionCount++;
        send(reply_port, message);

      }
    }
    else if(op_code == 2)
    {
      //Normal write to file - but check for the file size
      char buff[8];
      //strcpy(buff, message->msg);
      int len = 0;
      for(int i=0; i<8; i++)
      {
        buff[i] = message->msg[i+2];
        if(message->msg[i+2] != 0)
        len++;
      }

      char filename[25];
      strcpy(filename, serverFileNames[reply_port-1]);
      //strcat(filename, ".server");

      printf("Server: transfer request from client %d\n", message->msg[1]);
      printf("File %s opened for writing\n", filename);
      //fptr = fopen("f1.server","a");

      fptr = fopen(filename,"r");
      fseek(fptr, 0, SEEK_END);
      int sz =ftell(fptr);
      fclose(fptr);

      message_t *message = malloc(sizeof(message_t));
      message->next = '\0';
      //message->reply_port = server_port;
        message->msg[1] = server_port;

      printf("Server : size of the file written so far = %d\n", sz);

      if(sz + strlen(buff)> 1024000)
      {
          // file size limit exceeded so stop exection
          //message->status = 500;
          message->msg[0] = 500;
          send(reply_port, message);
          //Reduce the client connection count  - client no longer communicate with server when the file size limit reached.
          clientConnectionCount--;
          continue;
      }

      fptr = fopen(filename,"a");
      fwrite(buff, 1, len * sizeof(char), fptr);
      fclose(fptr);
      printf("File %s closed after writing\n", filename);
      printf("Server : sending ACK message to the client %d\n", message->msg[1]);
      send(reply_port, message);
      printf("Server : transfer request completed for client %d\n", message->msg[1]);
    }
    else if(op_code ==201)
    {
      //fclose(fptr);
      printf("Server: complete request from client %d\n", message->msg[1]);
      printf("Server close the connection..\n");
      clientConnectionCount--;
      send(message->msg[1], message);
    }
    else
    {
      printf("Server : Undefined request from client %d with op code %d\n", message->msg[1],message->msg[0]);
    }
  }
}


void client()
{

  int i;
  P(&mutex);
  int client_port = ++client_port_number;
  V(&mutex);

  printf("\nclient%d started..\n", client_port);

  int server_port = 0;
  init_port(client_port);

  char file_name[100];
  strcpy(file_name, clientFileNames[client_port-1]);

  init_port(client_port);
  FILE *fptr = fopen(file_name,"r");

  char buffer[8];


  //fread(buffer, 1, 8, fptr);

  int terminate = 0;

  //Start create file
  while(1)
  {
    message_t *message = malloc(sizeof(message_t));
    message->next = '\0';
    //message->reply_port = client_port;
    message->msg[0] = 1;
    message->msg[1] = client_port;
    //message->filename = file_name;
    //strcpy(message->msg, buffer);
    /*for(int i=2 ; i<10; i++)
    {
      message->msg[i] = buffer[i-2];
    }*/

    int nameLength = strlen(file_name);
    printf("length = %d", nameLength);
    int msgIndex = 2, charIndex = 0;

    for (int i=0; i<nameLength && msgIndex <10; i+=4) {
    char packet[4];
    packet[0] = charIndex < nameLength ? file_name[charIndex++] : '\0';
    packet[1] = charIndex < nameLength ? file_name[charIndex++] : '\0';
    packet[2] = charIndex < nameLength ? file_name[charIndex++] : '\0';
    packet[3] = charIndex < nameLength ? file_name[charIndex++] : '\0';
    message->msg[msgIndex++] = packToInt(packet);
    }
    //message->status = 1;

    send(server_port, message);
    receive(client_port, &message);
    int status = message->msg[0];

    if(status == 200)
    {
      printf("Client %d : Connection implemented with the file server \n", client_port);
      break;
    }
    else if(status == 300)
    {
      //server busy
      //yield();
      printf("Client %d is trying to establish connection\n", client_port);
      terminate = 1;
      break;
      //continue;
    }
    else if(status == 400)
    {
      // file name is not valid
      printf("File name is invalid so aborting client %d", client_port);
      terminate = 1;
      break;
    }
    else
    {
      terminate = 1;
    }
  }

  if(terminate == 0)
  {
    int charRead = fread(buffer, 1, 8, fptr);
    printf("Sending data to the file server..");
    while(charRead == 8) {
      /* byte swap here */
      printf("In client %d read = %s\n", client_port, buffer);
      char test[8];

      message_t *message = malloc(sizeof(message_t));
      //message->next = '\0';
      //message->reply_port = client_port;
      //message->filename = file_name;
      //strcpy(message->msg, buffer);
      //message->status = 2;
      message->next = '\0';
      //message->reply_port = client_port;
      message->msg[0] = 2;
      message->msg[1] = client_port;
      //message->filename = file_name;
      //strcpy(message->msg, buffer);

      for(int i=2 ; i<10; i++)
      {
        message->msg[i] = buffer[i-2];
      }

      send(server_port, message);
      printf("Client waiting for ACK of previous send\n");
      receive(client_port, message);
      printf("In client %d received ACK\n", client_port);
      printf("In client %d message status = %d", client_port, message->msg[0]);

      if(message->msg[0] == 500)
      {
        // File size exceeded 1 MB
        terminate = 1;
        break;
      }
      charRead = fread(buffer, 1, 8, fptr);
    }

    if(charRead >0)
    {
      message_t *message = malloc(sizeof(message_t));
      message->next = '\0';
      message->next = '\0';
      //message->reply_port = client_port;
      message->msg[0] = 2;
      message->msg[1] = client_port;

      for(int i=2 ; i<10; i++)
      {
        message->msg[i] = buffer[i-2];
      }

      send(server_port, message);
      printf("Client waiting for ACK of previous send\n");
      receive(client_port, message);
      printf("In client %d received ACK\n", client_port);
      printf("In client %d message status = %d", client_port, message->msg[0]);

      if(message->msg[0] == 500)
      {
        // File size exceeded 1 MB
        terminate = 1;
      }
    }
  }

  //Once the file read is complete, terminate the thread (yield)
  if(terminate ==0)
  {
    // Send message to close the file pointer
    message_t *message = malloc(sizeof(message_t));
    //message->next = '\0';
    //message->reply_port = client_port;
    //message->filename = file_name;
    //message->status = 201;
    message->msg[0] = 201;
    message->msg[1] = client_port;

    printf("Client %d : Sent message to server to close the file", client_port);
    send(server_port, message);
    receive(client_port, message);
    printf("Client %d : File transfered successfully...", client_port);
  }

  while(1)
  {
    printf("Client : %d Yield...\n", client_port);
    //sleep(1);
    yield();
  }
}

//-------------------------------------------------------
int main(int argc, char *argv[])
{
  init_readyQueue();
  mutex = CreateSem(1);
  int i;

  start_thread(server);
  for(i=0;i<argc-2;i++){
	   strcpy(clientFileNames[i], argv[i+2]);
     printf("%s\n",argv[i+1]);
     start_thread(client);

  }

  run();
}
