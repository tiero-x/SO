#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int dato=0;
int turno=0;
int flag[2]={0,0};

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
    pthread_attr_init(&attr);
    pthread_create(&tid1,&attr,resta,NULL);
    pthread_create(&tid2,&attr,suma,NULL);
    printf("dato = %d\n", dato);
}

/** Este hilo resta */
void *resta()
{
  int t=0;
  flag[1]=1;
  turno=0;
  while(flag[1] && turno==1);
  int temp=dato;
  for(int i=0;i<=1000000000;i++)
  {
    t++;
  }
  temp-=t/10000000;
  dato=temp;
  flag[1]=0;
  pthread_exit(0);
}


/** Este hilo suma */
void *suma()
{
  int t=0;
  flag[0]=1;
  turno=1;
  while(flag[0] && turno==0);
  int temp=dato;
  for(int i=0;i<=500000;i++)
  {
    t++;
  }
  temp-=t/10000;
  dato=temp;
  flag[0]=0;
  pthread_exit(0);
}
