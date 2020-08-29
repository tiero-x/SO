#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int *num, sum=0;

void *sorter (void *param);
int comp(const void * a, const void *b);

int main(int argc, int argv[])
{
  pthread_t thread[j];
  pthread_attr_t attr;
  int j=0, lim = atoi(argv[1]);
  long t;

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

    num=malloc(*sizeof(int));
    for(int i=0;i<lim;i++)
      {
        num[i]=random()%500;
      }

      int lim1[]={0,lim};

      printf("Cuantos hilos deseas usar? ");
      scanf("%d", &j);
      for(t=0;t<=j;t++)
      {
      pthread_attr_init(&attr);
      pthread_create(&tid,&attr,sorter,(void *)t);
    }
    pthread_exit(0);

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
}

void *sorter(void *param)
{
  int *par=(int*)param;
  int lower=par[0];
  int i,upper=par[1];

  qsort(&num[lower],upper-lower,sizeof(int),comp);
  pthread_exit(0);
}

int comp(const void * a, const void * b)
{
  return (*(int*)a - *(int*)b);
}
