#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
void *th1 (void * arg)
{
    while(1)
    {
        printf("发送视频\n");
        sleep(1);
    }
    return NULL;
}
void *th2 (void * arg)
{
    while(1)
    {
        printf("接受控制\n");
        sleep(1);
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    
    pthread_t tid1,tid2;
    pthread_create(&tid1,NULL,th1,NULL);
    pthread_create(&tid2,NULL,th2,NULL);

    while(1);
    return 0;
}
