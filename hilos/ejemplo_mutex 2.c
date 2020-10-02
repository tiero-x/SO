#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int dato=0;
int turno=0;
pthread_mutex_t *mutexlock;

void* resta();
void* suma();

int main(int argc,char *argv[])
{
  pthread_t tid1,tid2;
  pthread_attr_t attr;

  if(argc != 2)
    {
      fprintf(stderr,"usage: a.out <integer value>\n");
      return -1;
    }

  if(atoi(argv[1])<0)
    {
      fprintf(stderr,"Argument %d must be non-negative\n",atoi(argv[1]));
      return -1;
    }

    dato=atoi(argv[1]);

    mutexlock=(pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(mutexlock,NULL);

    pthread_attr_init(&attr);
    pthread_create(&tid1,&attr,resta,NULL);
    pthread_create(&tid2,&attr,suma,NULL);
    printf("dato = %d\n", dato);
}

/** Este hilo resta */
void *resta()
{
  int t=0;
  pthread_mutex_lock(mutexlock);
  int temp=dato;
  for(int i=0;i<=1000000000;i++)
  {
    t++;
  }
  temp-=t/10000000;
  dato=temp;
  pthread_mutex_unlock(mutexlock);
  pthread_exit(0);
}


/** Este hilo suma */
void *suma()
{
  int t=0;
  pthread_mutex_lock(mutexlock);
  int temp=dato;
  for(int i=0;i<=500000;i++)
  {
    t++;
  }
  temp-=t/10000;
  dato=temp;
  pthread_mutex_unlock(mutexlock);
  pthread_exit(0);
}
