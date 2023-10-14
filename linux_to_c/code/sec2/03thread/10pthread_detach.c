#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
void *th1 (void * arg)
{
    pthread_detach(pthread_self());
    return NULL;
}

int main(int argc, char *argv[])
{
    int i = 0 ;
    pthread_t tid1;
    for(i = 0 ;i<50000;i++)
    {
    
        int ret = pthread_create(&tid1,NULL,th1,NULL);
        if(0 !=ret)
        {
        
            break;
        }
        printf("i:%d\n",i);
    }

    return 0;
}
