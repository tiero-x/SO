#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct proceso{

  int pid;
  int rafagas_CPU[11];
  int rafagas_ES[10];
  int tiempo_llegada;
  int waiting_time;
  int turnaround_time;
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
  int sum_waiting_time = 0, sum_turnaround_time;
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

    proc[i].waiting_time = proc[i].turnaround_time = 0;
}

// calculate waiting time and turnaround time
proc[0].turnaround_time = proc[0].burst_time;

for(i=1; i<20; i++) {
    proc[i].waiting_time = proc[i-1].waiting_time + proc[i-1].burst_time;
    proc[i].turnaround_time = proc[i].waiting_time + proc[i].burst_time;
}

// calculate sum of waiting time and sum of turnaround time
for(i=0; i<20; i++) {
        sum_waiting_time += proc[i].waiting_time;
        sum_turnaround_time += proc[i].turnaround_time;
}

// print table
puts(""); // Empty line
print_table(p, n);
puts(""); // Empty Line
printf("Total Waiting Time      : %-2d\n", sum_waiting_time);
printf("Average Waiting Time    : %-2.2lf\n", (double)sum_waiting_time / (double) n);
printf("Total Turnaround Time   : %-2d\n", sum_turnaround_time);
printf("Average Turnaround Time : %-2.2lf\n", (double)sum_turnaround_time / (double) n);

// print Gantt chart
puts(""); // Empty line
puts("          GANTT CHART          ");
puts("          ***********          ");
print_gantt_chart(p, 20);
return 0;
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
