#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
void *th1 (void * arg)
{
    int i = 5;
    while(i--)
    {
        printf("发送视频 tid:%ld\n",pthread_self());
        sleep(1);
    }
//    return NULL;
    printf("th1 exit\n");
    pthread_exit(NULL);
}
void *th2 (void * arg)
{
    int i = 5;
    while(i--)
    {
        printf("接受控制 tid:%ld\n",pthread_self());
        sleep(1);
    }
    printf("th2 exit\n");
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    
    pthread_t tid1,tid2;
    pthread_create(&tid1,NULL,th1,NULL);
    pthread_create(&tid2,NULL,th2,NULL);
    int i =2;
    while(i--)
    {
        
        printf("main th tid:%ld\n",pthread_self());
        sleep(3);
    }
    return 0;
}
