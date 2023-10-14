

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
sem_t sem_win;
void* th(void* arg)
{
    sem_wait(&sem_win);
    printf("get win tid:%ld\n",pthread_self());
    int sleep_time = rand()%5 ;
    sleep(sleep_time);
    printf("release win %ld\n",pthread_self());
    sem_post(&sem_win);
    return NULL;

}

int main(int argc, char *argv[])
{
    int i = 0 ;
    sem_init(&sem_win,0,3);

    pthread_t tid[10]={0};
    for(i=0;i<10;i++)
    {
    
        pthread_create(&tid[i],NULL,th,NULL);
    }

    for(i = 0 ;i<10;i++)
    {
        pthread_join(tid[i],NULL);
    }
    sem_destroy(&sem_win);
    return 0;
}
