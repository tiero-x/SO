#include <curses.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

struct s_dir{
  int tipo;
  char *nombre;
} res[128];

int leeDir(char *direc){
  DIR *dir = opendir(direc);

  struct dirent *dp;
  int i=0;
  while((dp=readdir(dir))!= NULL){
    res[i].tipo=dp->d_type;
    res[i].nombre=strdup(dp->d_name);
    i++;
  }
  closedir(dir);
  return i;
}

int main()
{
  char cwd[256];

  getcwd(cwd,256);
  int max=leeDir(cwd);
  int i=0;
  int c;
  int sigue=1;
  int offset=0;
  int num=0;

  initscr();
  raw();
  noecho(); //No mostar caracter leido

  do{
    for(int j=0;(j+offset)<max && j<num;j++){
      if(j==i){
        attron(A_REVERSE);
      }
      char *nom=res[j+offset].nombre;
      mvprintw(5+j,4,nom);
      clrtoeol();
      attroff(A_REVERSE);
    }
    move(5+i,4);
    refresh();
    c=getch();
    switch(c){
      case 'A':
      i=(i>0) ? i-1 : max-1;
      break;
      case 'B':
      if(i<(num-1)){
        i += 1;
      }
      else {
        if((offset+1)<max){
          offset += 1;
        }
        else{
          i=offset=0;
          clear();
        }
      }
      break;
      case 10:
      if(strcmp(".",res[i].nombre)==0 || res[i].tipo==DT_REG){
        // Si es un archivo, se sale
        if(res[i].tipo==DT_REG){
          sigue=0;
        }
      } else {
        if(strcmp("..",res[i].nombre)==0){
          // Cambia al papá
          char *p=strrchr(cwd,'/');
          *p=0;
          max=leeDir(cwd);
          i=0;
          clear();
        } else {
          // Cambia a otro directorio
          strncat(cwd,"/",256);
          strncat(cwd,res[i].nombre,256);
          max=leeDir(cwd);
          i=0;
          clear();
        }
      }
      break;
      default:
      // Nada
      break;
    }
    move(2,10);
    printw("Estoy en %d: Leí: %d Num: %d Dir: %s",i,c,max,cwd);
  } while (c!='q' && sigue);
  if(sigue==0){
    clear();
    move(2,10);
    printw("Elegiste %s", res[i].nombre);
    getch();
  }
  endwin();
  return 0;
}
