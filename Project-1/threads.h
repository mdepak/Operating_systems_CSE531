// (c) Partha Dasgupta 2009
// permission to use and distribute granted.

#include <pthread.h>

pthread_t start_thread(void *func, int *arg)
  {
   pthread_t thread_id;
   int rc;
      printf("In main: creating thread\n");
      rc = pthread_create(&thread_id, NULL, func, arg);
      if (rc){
         printf("ERROR; return code from pthread_create() is %d\n", rc);
         exit(-1);
        }
    return(thread_id);
   }



