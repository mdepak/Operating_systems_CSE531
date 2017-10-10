#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "sem.h"

#define _GNU_SOURCE

//Team mates:
/*
Anudeep Sanepalli -   1210442230
Deepak Mahudeswaran - 1213175078
*/

/*
To run:
gcc -pthread proj-1.c

Ignore any warnings and execute.
*/

int arr[]={0,0,0};
semaphore_t t1_full,t2_full,t3_full,main_full,mutex;

void function_1(int *arg)
{
  int threadId = *arg;
  printf("Started child thread %d\n", threadId);

  while (1){
    P(&t1_full);
    P(&mutex);
    printf("In thread %d, Incrementing the array variable\n",threadId);
    arr[0]++;
    V(&mutex);
    V(&main_full);
    sleep(1);
  }
}

void function_2(int *arg)
{
  int threadId = *arg;
  printf("Started child thread %d\n", threadId);

  while (1){
    P(&t2_full);
    P(&mutex);
    printf("In thread %d, Incrementing the array variable\n",threadId);
    arr[1]++;
    V(&mutex);
    V(&main_full);
    sleep(1);
  }
}

void function_3(int *arg)
{
  int threadId = *arg;
  printf("Started child thread %d\n", threadId);

  while (1){
    P(&t3_full);
    P(&mutex);
    printf("In thread %d, Incrementing the array variable\n",threadId);
    arr[2]++;
    V(&mutex);
    V(&main_full);
    sleep(1);
  }
}

int main()
{  int arg;
  int i;
  int id[10] = {0, 1, 2};

  init_sem(&t1_full, 1);
  init_sem(&t2_full, 1);
  init_sem(&t3_full, 1);
  init_sem(&main_full, 0);
  init_sem(&mutex, 1);

  start_thread(function_1, &id[0]);
  start_thread(function_2, &id[1]); // there is a serious bug here, left it in for demo purposes
  start_thread(function_3, &id[2]);

  while(1) {

    P(&main_full);
    P(&main_full);
    P(&main_full);
    P(&mutex);
    printf("In main thread() - %d\t %d\t %d\t \n",arr[0],arr[1],arr[2]);
    V(&mutex);
    V(&t1_full);
    V(&t2_full);
    V(&t3_full);
    sleep(1);
  } // infinite loop

  return 0;
}
