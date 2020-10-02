#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int *num;
int sum=0;

void* sorter(void *param);

int comp(const void * a, const void * b)
{
  return (*(int*)a - *(int*)b);
}

int main(int argc, char *argv[])
{
  pthread_t tid;
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

  int lim=atoi(argv[1]);
  num=malloc(lim *sizeof(int));
  for(int i=0;i<lim;i++)
    {
      num[i]=random()%100;
    }

  int lim1[]={0,lim};

  pthread_attr_init(&attr);
  pthread_create(&tid,&attr,sorter,&lim1);
  pthread_join(tid,NULL);

  for(int i=0;i<lim;i++)
    {
      printf("%d ",num[i]);
    }
  printf("\n");

  qsort(num,lim,sizeof(int),comp);

  for(int i=0;i<lim;i++)
    {
      printf("%d ",num[i]);
    }
  printf("\n");
}

void* sorter(void *param)
{
  int *par=(int*)param;
  int lower=par[0];
  int i,upper=par[1];

  qsort(&num[lower],upper-lower,sizeof(int),comp);
  pthread_exit(0);
}
