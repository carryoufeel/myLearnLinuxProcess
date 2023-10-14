#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
void *f1(void *arg)
{
	while(1)
	{
		printf("i'm f1:%ld\n",pthread_self());
		sleep(1);
	}
}
void *f2(void *arg)
{
	while(1)
	{
		printf("i'm f2:%ld\n",pthread_self());
		sleep(1);
	}
}
int main()
{
	int i=0;
	pthread_t th1,th2;
	pthread_create(&th1,NULL,f1,NULL);
	pthread_create(&th2,NULL,f2,NULL);
	while(1)
	{
		i++;
		printf("i'm master,%d,id%ld\n",i,pthread_self());
		sleep(1);
		if(i==5)
		{
			pthread_cancel(th1);
		}
		else if(i==10)
		{
			pthread_cancel(th2);
		}
		else if(i==20)
		{

			pthread_exit(NULL);
		}
	}
	return 0;
}
