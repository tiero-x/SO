#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#define NUM_THREADS 5

void *print_hello(void *threadid)
{
  long tid;
  tid = (long)threadid;
  printf("Hello World! It's me, thread #%1d!\n",tid);
  pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
  pthread_t threads[NUM_THREADS];
  int rc;
  long t;
  
  for(t=0;t<=NUM_THREADS;t++)
    {
      printf("In main: creating thread %1d\n",t);
      rc=pthread_create(threads+t,NULL,print_hello,(void *)t);
      if(rc)
	{
	  printf("ERROR; return code from pthread_create() is %d\n",rc);
	  exit(-1);
	}
    }
  pthread_exit(NULL);
}
