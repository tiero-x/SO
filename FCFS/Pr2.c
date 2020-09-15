#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct proceso{

  int pid;
  int rafagas_CPU[11];
  int rafagas_ES[10];
  int tiempo_llegada;
  int tiempo_espera;
  int tiempo_vuelta;
  int tat;
};

typedef struct proceso procesos;

procesos proc[20];
void generador_procesos( int ale);
void imprimir_procesos(int ale);
int generar_aleatorio();
int tiempo();

int main(void){
  int aleatorio =0;
  aleatorio = generar_aleatorio ();
  generador_procesos (aleatorio);
  imprimir_procesos (aleatorio);
  tiempo();
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
  }
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

int tiempo()
{
  int total_wt=0, total_tat=0;

    proc[0].tiempo_espera = 0;

    for(int i=1;i<proc[i].pid;i++)
    {
      proc[i].tiempo_espera = proc[i-1].rafagas_CPU[i] + proc[i-1].tiempo_espera;
    }

    for (int i=0;i<proc[i].pid;i++)
    {
      proc[i].tat=proc[i].tiempo_espera + proc[i].rafagas_CPU[i];
    }

  printf("Procesos  Rafaga  Tiempo de espera  Tiempo de llegada\n");
  for(int i=0;i<proc[i].pid;i++)
  {
    total_wt = total_wt + proc[i].tiempo_espera;
    total_tat= total_tat + proc[i].tat;
    printf("%d", (i+1));
    printf("%d", proc[i].rafagas_CPU[i]);
    printf("%d", proc[i].tiempo_espera);
    printf("%d", proc[i].tat);
  }
  int i;
  int s=(float)total_wt/(float)proc[i].pid;
  int t=(float)total_tat/(float)proc[i].pid;
  printf("Tiempo de espera = %d\n",s);
  printf("Tiempo de vuelta = %d\n",t);
}
