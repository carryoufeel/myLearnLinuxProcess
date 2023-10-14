#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

void clean(void * arg)
{   

    printf("clean fun ,arg %s\n",(char*)arg);
    free(arg);
    return ;
}
void *th1 (void * arg)
{
    pthread_cleanup_push(clean,arg);
    char* tmp = (char* )arg;

    strcpy(tmp,"hello");
    printf("th1 arg %s\n",(char*)arg);

    pthread_cleanup_pop(1);
    return NULL;
}

int main(int argc, char *argv[])
{
    int i = 0 ;
    pthread_t tid1;
    char * p =(char*) malloc(50);
    int ret = pthread_create(&tid1,NULL,th1,p);
    if(0 !=ret)
    {

        perror("pthread_create");
        return 1;
    }
    printf("before join\n");
    pthread_join(tid1,NULL);
    printf("after join\n");

    return 0;
}
