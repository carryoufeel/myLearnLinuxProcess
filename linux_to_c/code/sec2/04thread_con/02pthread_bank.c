

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
int win = 3;
pthread_mutex_t mutex;
void* th(void* arg)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);
        if(win>0)
        {

            win--;
            pthread_mutex_unlock(&mutex);
            printf("get win tid:%ld\n",pthread_self());
            int sleep_time = rand()%5 ;
            sleep(sleep_time);
            pthread_mutex_lock(&mutex);
            win++;
            printf("release win %ld\n",pthread_self());
            pthread_mutex_unlock(&mutex);
            break;

        }
        else 
        {

            pthread_mutex_unlock(&mutex);
        }
    }



    return NULL;

}

int main(int argc, char *argv[])
{
    int i = 0 ;
    pthread_t tid[10]={0};
    pthread_mutex_init(&mutex,NULL);
    for(i=0;i<10;i++)
    {
    
        pthread_create(&tid[i],NULL,th,NULL);
    }

    for(i = 0 ;i<10;i++)
    {
        pthread_join(tid[i],NULL);
    }
    
    pthread_mutex_destroy(&mutex);
    return 0;
}
