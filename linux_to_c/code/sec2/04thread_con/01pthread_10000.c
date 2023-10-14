
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
int a = 0 ;
pthread_mutex_t  mutex;
void* th(void* arg)
{
    int i = 5000;
    while(i--)
    {
    
    pthread_mutex_lock(&mutex);
        int tmp = a;
        printf("a:%d\n",tmp+1);
        a = tmp+1;
    pthread_mutex_unlock(&mutex);
        
    }
    return NULL;

}

int main(int argc, char *argv[])
{

    pthread_t tid1,tid2;
    pthread_mutex_init(&mutex,NULL);
    pthread_create(&tid1,NULL,th,NULL);
    pthread_create(&tid2,NULL,th,NULL);
    
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    
    pthread_mutex_destroy(&mutex);
    return 0;
}
