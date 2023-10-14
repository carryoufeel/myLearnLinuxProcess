#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>


typedef struct 
{
    char name[50];
    int age;
    char addr[50];

}Person;
void *th1 (void * arg)
{
    Person* tmp = (Person*)arg;
    printf("name %s age %d addr %s\n",tmp->name,tmp->age,tmp->addr);
    return arg;
}

int main(int argc, char *argv[])
{
    
    pthread_t tid1;
    Person per;
    bzero(&per,sizeof(per));
    printf("input name");
    fgets(per.name,sizeof(per.name),stdin);
    per.name[strlen(per.name)-1]='\0';
    char tmp[5]={0};
    printf("input age");
    fgets(tmp,sizeof(tmp),stdin);//11\n
    per.age  = atoi(tmp);

    printf("input addr");
    fgets(per.addr,sizeof(per.addr),stdin);

    pthread_create(&tid1,NULL,th1,&per);
    pthread_join(tid1,NULL);

    return 0;
}
