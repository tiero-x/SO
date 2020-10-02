#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int hazFork()
{
  int id = fork();
  int x = 10;
  
  if(id == 0) {
    sleep(0);
    x = x + 5;
    printf("El primero vale %d\n", x);
}
  else {
    sleep(20);
    x = x - 5;
    printf("El segundo vale %d\n", x);
  }
}

int main ()
{
  hazFork();
  hazFork();
}

