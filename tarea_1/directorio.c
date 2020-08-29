#include <stdio.h>
#include <dirent.h>

int main()
{
  DIR *directorio;
  struct dirent *entrada;
  int archivos = 0;
  
  directorio = opendir(".");
  if(directorio == NULL)
    {
      perror("No se puede abrir el directorio");
      return(1);
    }
  while ((entrada=readdir(directorio)))
    {
      archivos++;
      printf("Archivo %3d: %s\n", archivos, entrada->d_name);
    }
  closedir(directorio);

  return (0);
}
