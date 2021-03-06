#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex;
sem_t lleno;
sem_t vacio;
int datos[5];

void* produce();
void* consume();

int main(int argc, char *argv[])
{
  pthread_t tid1,tid2;
  pthread_attr_t attr;

  sem_init(&vacio,0,5); //Numero de veces que puedo entrar a producir
  sem_init(&mutex,0,1); //Cuantos pueden entrar a la seccion critica
  sem_init(&lleno,0,0); //Cuantas cosas hay en el buffer
  
  pthread_attr_init(&attr);
  pthread_create(&tid1,&attr,consume,NULL);
  pthread_create(&tid2,&attr,produce,NULL);
  pthread_join(tid1,NULL);
  pthread_join(tid2,NULL);
}

/**
* Este proceso lo produce
*/
void* produce()
{
  int cc=0; //Cola circular
  int i=0; //Veces

  do {
    sem_wait(&vacio);
    sem_wait(&mutex);
    datos[cc] = random() % 100;
    printf("Produje %d\n",datos[cc]);
    cc = (cc < 4) ? cc+1 : 0;
    sem_post(&mutex);
    sem_post(&lleno);
    i++;
    } while(i<20);
  pthread_exit(0);
}

/**
* Este proceso lo cambia
*/
void* consume()
{
  int cc=0; //Cola circular
  int i=0; //Veces
  while (i<20) {
    sem_wait(&lleno); //Checa si hay algo
    sem_wait(&mutex);
    printf("Dato anterior %d\n",datos[cc]);
    datos[cc] +=5;
    printf("Dato actual %d\n", datos[cc]);
    cc = (cc < 4) ? cc+1 : 0;
    sem_post(&mutex);
    sem_post(&lleno);
    i++;
    sleep(2);
  }
pthread_exit(0);
}
