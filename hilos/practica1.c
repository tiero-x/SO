#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/sysinfo.h>
#include <time.h>

int *num;
int sum=0;
int j=0;

void *sorter (void *param);

int comp(const void * a, const void *b)
{
  return (*(int*)a - *(int*)b);
}

int main(int argc, char *argv[])
{
  pthread_t tid [j];
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
  
  printf("El sistema tiene %d procesadores configurados y %d procesadores disponibles.\n", get_nprocs_conf(),get_nprocs());
  
  int lim=atoi(argv[1]);
  num=malloc(lim *sizeof(int));
  for(int i=0;i<lim;i++)
    {
      num[i]=random()%500;
    }
  
  int lim1[]={0,lim};
  long x;
  
  printf("Cuantos hilos quieres ocupar? ");
  scanf("%d",&j);
  
  for(x=0;x<j;x++)
    {
      pthread_attr_init(&attr);
      pthread_create(&tid[j],&attr,sorter,&lim1);
      pthread_join(tid[j],NULL);
      
      clock_t t;
      t=clock();
      qsort(num,lim,sizeof(int),comp);
      t=clock()-t;
      double time_taken = ((double)t)/CLOCKS_PER_SEC;
      
      for(int i=0;i<lim;i++)
	{
	  printf("%d ",num[i]);
	}
      printf("\nEste hilo se ejecuto en %f segundos\n\n",time_taken);
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
