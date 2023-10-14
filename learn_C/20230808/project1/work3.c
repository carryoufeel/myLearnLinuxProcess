#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
int a=10;
void *f1(void *arg)
{
	//(int)*(arg+1)=1;
	while(1)
	{
		printf("i'm f1:%ld\n",pthread_self());
		a++;
		printf("f1 value:%d\n",a);
		sleep(1);
	}
}
void *f2(void *arg)
{
	//arg+2=2;
	while(1)
	{
		printf("i'm f2:%ld\n",pthread_self());
		a--;
		printf("f2 value:%d\n",a);
		sleep(1);
	}
}
int main()
{
	int i=0;
	pthread_t th1,th2;
	int *p=malloc(10);
	pthread_create(&th1,NULL,f1,p);
	pthread_create(&th2,NULL,f2,p);
	while(1)
	{
		i++;
		printf("i'm master,%d,id%ld,value%d\n",i,pthread_self(),a);
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
	free(p);
	return 0;
}
