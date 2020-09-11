#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
  for(int i=1;i<21;i++)
    {
      if(fork() == 0)
	{
	  printf("Hijo %d: pid [%d] y pid de padre [%d]\n", i, getpid(),getppid());
	  exit(0);
	}
    }
  for(int i=1;i<21;i++)
    wait(NULL);
}
