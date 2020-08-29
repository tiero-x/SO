#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main()
{
  char *args[]={"./eje",NULL};

  int id = fork();

  if(id != 0) {
    printf("El primero");
  }
  else {
    printf("El segundo");
    execvp(args[0],args);
  }

  wait(NULL);
  printf("Ya termine\n");
}
