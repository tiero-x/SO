#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

sem_t mutex;

void* thread(void* arg)
{
    //wait
    sem_wait(&mutex);
    printf("\nEntre a comer\n");

    //critical section
    sleep(4);

    //signal
    printf("\nSali de comer\n");
    sem_post(&mutex);
}


int main()
{
    sem_init(&mutex, 0, 1);
    pthread_t t1,t2,t3,t4;
    pthread_create(&t1,NULL,thread,NULL);
    sleep(2);
    pthread_create(&t2,NULL,thread,NULL);
    sleep(4);
    pthread_create(&t3,NULL,thread,NULL);
    sleep(1);
    pthread_create(&t4,NULL,thread,NULL);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);
    pthread_join(t4,NULL);
    sem_destroy(&mutex);
    return 0;
}
