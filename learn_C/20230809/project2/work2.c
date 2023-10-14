#include<stdio.h>
#include<pthread.h>
#include <stdlib.h>
#include<unistd.h>
#include<semaphore.h>
sem_t win;
void *peopel(void *arg)
{
	sem_wait(&win);
	int a=rand()%5;
	printf("peopel%ldstart\n",pthread_self());
	sleep(a);
	printf("peopel%ldfinsh\n",pthread_self());
	sem_post(&win);
	return NULL;
}
int main()
{
	pthread_t th[10]={0};
	sem_init(&win,0,3);
	int i=0;
	for(;i<10;)
	{
		pthread_create(&th[i],NULL,peopel,NULL);
		i++;
	}
	for(i=0;i<10;)
	{
		pthread_join(th[i],NULL);
		i++;
	}
	sem_destroy(&win);
}
