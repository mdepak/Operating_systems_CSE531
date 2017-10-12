#include <stdio.h>
#include "threads.h"

int global = 1;

void function1(void)
{
  int local = 1;
  while(1)
  {
    printf("In function 1 gloabl = %d\n", global);
    printf("In function 1 local = %d\n", local);
    printf("In function 1 incrementing global and local...\n");
    global++;
    local++;
    sleep(1);
    yield();
  }
}

void function2(void)
{
  int local = 1;
  while(1)
  {
    printf("In function 2 gloabl = %d\n", global);
    printf("In function 2 local = %d\n", local);
    printf("In function 2 incrementing global and local...\n");
    global++;
    local++;
    sleep(1);
    yield();
  }
}

void function3(void)
{
  int local = 1;
  while(1)
  {
    printf("In function 3 gloabl = %d\n", global);
    printf("In function 3 local = %d\n", local);
    printf("In function 3 incrementing global and local...\n");
    global++;
    local++;
    sleep(1);
    yield();
  }
}

int main(int argc, char *argv[])
{
  init_readyQueue();
  start_thread(function1);
  start_thread(function2);
  start_thread(function3);
  run();

  return 0;
}
