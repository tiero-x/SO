#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define MAX 100

struct proceso{

  int pid;
  int rafagas_CPU[11];
  int rafagas_ES[10];
  int tiempo_llegada;
  int tiempo_espera;
  int tiempo_vuelta;
};

typedef struct proceso procesos;

procesos proc[20];
void generador_procesos(int ale);
void imprimir_procesos(int ale);
int generar_aleatorio();
void tabla(proceso p[]);
void grafico(proceso p[]);

int main(void){
  proceso p[MAX];
  int aleatorio = 0;
  aleatorio = generar_aleatorio ();
  generador_procesos (aleatorio);
  imprimir_procesos (aleatorio);
}

void generador_procesos(int ale){
  int temp=0;
  srand(time(NULL));

  for(int i =0;i<20;i++){
    proc[i].pid = i;
    for(int j =0;j<ale+1;j++){
      while(temp<10){
        temp =rand()%20;
      }
      if(j<ale){
        proc[i].rafagas_ES[j] = temp;
      }
      temp =0;
      while(temp<1){
        temp =rand()%8;
      }
      proc[i].rafagas_CPU[j] = temp;
    }
    if(i == 0){
      proc[0].tiempo_llegada =0;
    }
    else{
      proc[i].tiempo_llegada =rand()%20;
    }
  }
}

void imprimir_procesos(int ale){
  int suma_espera=0, suma_vuelta;
  for(int i=0;i<20;i++){
    printf("\n PROCESO # %d\n",i+1);
    printf("PID: %d\n",proc[i].pid);
    for(int j=0;j<ale+1;j++){
      printf("\nRAFAGAS %d\n",j+1);
      printf("RAFAGA CPU: %d\n",proc[i].rafagas_CPU[j]);
      if(j<ale){
        printf("RAFAGA E/S: %d\n",proc[i].rafagas_ES[j]);
      }
    }
    printf("\n");
    printf("LLEGADA: %d\n",proc[i].tiempo_llegada);
    printf("\n");
    proc[i].tiempo_espera = proc[i].tiempo_vuelta = 0;
  }

  proc[0].tiempo_vuelta = proc[0].rafagas_CPU[0];

  for(int i=1;i<20;i++){
    proc[i].tiempo_espera = proc[i-1].tiempo_espera + proc[i-1].rafagas_CPU[i-1];
    proc[i].tiempo_vuelta = proc[i].tiempo_espera + proc[i].rafagas_CPU[i];
  }

  for(int i=0;i<20;i++){
    suma_espera += proc[i].tiempo_espera;
    suma_vuelta += proc[i].tiempo_vuelta;
  }

  puts("");
  tabla(p);
  puts("");
  printf("Tiempo de espera: %-2d\n", suma_espera);
  printf("Tiempo de vuelta: %-2d\n", suma_vuelta);

  puts("");
  puts("           GRAFICO        ");
  puts("         ***********      ");
  grafico(p);
}

void tabla(proceso p[])
{
  puts("+-----+------------+--------------+-----------------+");
  puts("| PID | Burst Time | Waiting Time | Turnaround Time |");
  puts("+-----+------------+--------------+-----------------+");

  for(int i=0;i<20;i++) {
        printf("| %2d  |     %2d     |      %2d      |        %2d       |\n"
               , proc[i].pid, proc[i].rafagas_CPU, p[i].tiempo_espera, p[i].tiempo_vuelta);
        puts("+-----+------------+--------------+-----------------+");
}

void grafico(proceso p[])
{
  int i,j;
  printf("  ");
  for(i=0;i<20;i++){
    for(j=0;j<proc[i].rafagas_CPU[i]-1;j++){
      printf("  ");
      printf("P%d", p[i].pid);
    }
    for(int j=0;j<proc[i].rafagas_CPU[i]-1;j++){
      printf("  ");
      printf("|");
    }
  }
  printf("\n");
  for(i=0;i<20;i++){
    for(j=0;j<proc[i].rafagas_CPU[i];i++){
      printf("--");
      printf("  ");
    }
    printf("\n");
  }

  printf("0");
  for(i=0;i<20;i++){
    for(j=0;j<proc[i].rafagas_CPU[i];j++){
      printf("  ");
    }
    if(proc[i].tiempo_vuelta > 9){
      printf("\b");
    }
    printf("%d", proc[i].tiempo_vuelta);
  }
  printf("\n");
}

int generar_aleatorio()
{
  srand(time(NULL));
  int aleatorio =0;
  while(aleatorio<5){
    aleatorio=rand()%10;
  }
  return aleatorio;
}
