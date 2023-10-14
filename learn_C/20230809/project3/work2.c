#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
sem_t sem_win1,sem_win2;
int con=1;
void* th1(void* arg)
{
	sem_wait(&sem_win1);
	printf("1号窗口:");
	printf("%d张票\n",con);
	con++;
	sem_post(&sem_win2);
	return NULL;
}
void* th2(void* arg)
{
	sem_wait(&sem_win2);
	printf("2号窗口:");
	printf("%d张票\n",con);
	con++;
	sem_post(&sem_win1);
	return NULL;
}

int main(int argc, char *argv[])
{
	int i = 0 ;
	sem_init(&sem_win1,0,1);
	sem_init(&sem_win2,0,0);
	pthread_t tid[100]={0};
	while(1)
	{
		pthread_create(&tid[i],NULL,th1,NULL);
		pthread_create(&tid[i+1],NULL,th2,NULL);
		i++;
		if(i==100)
		{
			break;
		}
	}

	for(i = 0 ;i<10;i++)
	{
		pthread_join(tid[i],NULL);
	}
	sem_destroy(&sem_win1);
	sem_destroy(&sem_win2);
	return 0;
}
