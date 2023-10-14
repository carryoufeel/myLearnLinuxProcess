#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
void *th1(void *arg)
{
	while(1)
	{
		printf("pth1:id:%ld\n",pthread_self());
		sleep(1);
	}
	return NULL;
}
void *th2(void *arg)
{
	while(1)
	{
		printf("pth2:id:%ld\n",pthread_self());
		sleep(1);
	}
	return NULL;
}
int main()
{
	pthread_t tid1,tid2;
	pthread_create(&tid1,NULL,th1,NULL);
	pthread_create(&tid2,NULL,th2,NULL);
	printf("%ld\n",pthread_self());
	while(1)
	{
		printf("%ld\n",pthread_self());
		sleep(2);
	}
	return 0;
}
