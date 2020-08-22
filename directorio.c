#include <stdio.h>
#include <dirent.h>

int main()
{
    DIR *prueba;

    folder = opendir(".");
    if(prueba == NULL)
    {
        puts("No se puede leer el directorio");
        return(1);
    }
    else
    {
        puts("El directorio ha sido abierto");
    }
    closedir(prueba);

    return(0);
}
