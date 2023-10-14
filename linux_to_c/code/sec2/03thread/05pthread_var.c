#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
int a = 20;
void *th1 (void * arg)
{
    int i = 5;
    while(i--)
    {
        a-=3;

        printf("发送视频 a =%d\n",a);
        sleep(1);
    }
    return NULL;
}
void *th2 (void * arg)
{
    int i = 5;
    while(i--)
    {
        a-=2;
        printf("接受控制 a =%d\n",a);
        sleep(1);
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    
    pthread_t tid1,tid2;
    pthread_create(&tid1,NULL,th1,NULL);
    pthread_create(&tid2,NULL,th2,NULL);

    while(a>0)
    {
    
        printf("main th a %d\n",a);
        sleep(1);
    }
    return 0;
}
