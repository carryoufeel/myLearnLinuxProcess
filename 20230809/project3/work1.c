#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
sem_t sem_a,sem_b,sem_c;
void* th1(void* arg)
{
	int i = 10;
	while(i--)
	{
		sem_wait(&sem_a);
		printf("a");
		fflush(stdout);
		sem_post(&sem_b);
	}
	return NULL;
}
void* th2(void* arg)
{
	int i = 10;
	while(i--)
	{
		sem_wait(&sem_b);
		printf("b");
		fflush(stdout);
		sem_post(&sem_c);

	}
	return NULL;


}
void* th3(void* arg)
{
	int i = 10;
	while(i--)
	{
		sem_wait(&sem_c);
		printf("c");
		fflush(stdout);
		sleep(1);
		sem_post(&sem_a);

	}
	return NULL;
}
int main(int argc, char *argv[])
{

	pthread_t tid1,tid2,tid3;
	sem_init(&sem_a,0,1);
	sem_init(&sem_b,0,0);
	sem_init(&sem_c,0,0);
	pthread_create(&tid1,NULL,th1,NULL);
	pthread_create(&tid2,NULL,th2,NULL);
	pthread_create(&tid3,NULL,th3,NULL);
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	pthread_join(tid3,NULL);
	sem_destroy(&sem_a);
	sem_destroy(&sem_b);
	sem_destroy(&sem_c);
	putchar(10);
	return 0;

}
