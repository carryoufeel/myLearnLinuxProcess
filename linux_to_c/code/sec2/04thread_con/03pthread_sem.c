
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
sem_t sem_W,sem_H;
void* th1(void* arg)
{
    int i = 10;
    while(i--)
    {
        sem_wait(&sem_H);
        printf("hello ");
        fflush(stdout);
        sem_post(&sem_W);
    }
    return NULL;

}
void* th2(void* arg)
{
    int i = 10;
    while(i--)
    {
        sem_wait(&sem_W);
        printf("world\n");
        sleep(1);
        sem_post(&sem_H);
    }
    return NULL;

}
int main(int argc, char *argv[])
{
    
    pthread_t tid1,tid2;
    sem_init(&sem_H,0,1);
    sem_init(&sem_W,0,0);
    pthread_create(&tid1,NULL,th1,NULL);
    pthread_create(&tid2,NULL,th2,NULL);
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    sem_destroy(&sem_H);
    sem_destroy(&sem_W);
    return 0;
}
