#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
sem_t sem_W,sem_H;
void *f1(void *arg)
{
	int i=10;
	while(i)
	{
		sem_wait(&sem_H);
		i--;
		printf("Hello ");
		sem_post(&sem_W);
	}
	return NULL;
}
void *f2(void *arg)
{
	int i=10;
	while(i)
	{
		sem_wait(&sem_W);
		i--;
		printf("Wlord\n");
		sleep(2);
		sem_post(&sem_H);
	}
	return NULL;
}
int main()
{
	pthread_t th1,th2;
	sem_init(&sem_H,0,1);
	sem_init(&sem_W,0,0);
	pthread_create(&th1,NULL,f1,NULL);
	pthread_create(&th2,NULL,f2,NULL);
	pthread_join(th1,NULL);
	pthread_join(th2,NULL);
	sem_destroy(&sem_H);
	sem_destroy(&sem_W);

}
