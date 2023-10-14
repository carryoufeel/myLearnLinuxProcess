#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
void *th1 (void * arg)
{
    int i =5;
    while(i--)
    {
        printf("发送视频\n");
        sleep(1);
    }
    return NULL;
}
void *th2 (void * arg)
{
    int i =3;
    while(i--)
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

    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    return 0;
}
