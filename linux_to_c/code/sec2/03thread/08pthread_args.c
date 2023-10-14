#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
void *th1 (void * arg)
{
    char* tmp = (char* )arg;
    
    strcpy(tmp,"hello");

    return arg;
}

int main(int argc, char *argv[])
{
    
    char* p = (char*)malloc(50);
    pthread_t tid1;
    pthread_create(&tid1,NULL,th1,p);
    void* ret;
    pthread_join(tid1,&ret);

    printf("%s\n",(char*)ret);
    free(ret);
    return 0;
}
