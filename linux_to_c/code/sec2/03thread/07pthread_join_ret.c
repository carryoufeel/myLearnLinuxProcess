#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
void *th1 (void * arg)
{

    int i =3;
    while(i--)
    {
        printf("sub th %ld\n",pthread_self());
        sleep(1);
    }
    static char buf[]="我要消亡了";
//    return buf;
    pthread_exit(buf);
}

int main(int argc, char *argv[])
{
    
    pthread_t tid1,tid2;
    pthread_create(&tid1,NULL,th1,NULL);
    void* ret;
    pthread_join(tid1,&ret);

    printf("%s\n",(char*)ret);
    return 0;
}
