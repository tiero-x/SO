#include <stdio.h>
#include <time.h>

void tiempo()
{
  printf("Tiempo que tarda el programa en ejecutarse\n");
  printf("Presiona [ENTER] para continuar");

  while(1)
    {
      if(getchar())
	break;
    }
    printf("\n");
  }

int main()
{
  clock_t t;
  t = clock();
  tiempo();
  t = clock()-t;
  double time_taken = ((double)t)/CLOCKS_PER_SEC;

  printf("%f segundos\n", time_taken);
  return 0;
}

