#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
int a=10;
int b=10;
void *f1(void *arg)
{
	//(int)*(arg+1)=1;
	while(1)
	{
		printf("i'm f1:%ld\n",pthread_self());
		a--;
		printf("f1 value:%d\n",a);
		sleep(1);
		if(a==5)break;
	}
	strcpy((char*)arg,"hello");
	return arg;
}
void *f2(void *arg)
{
	//arg+2=2;
	while(1)
	{
		printf("i'm f2:%ld\n",pthread_self());
		b--;
		printf("f2 value:%d\n",a);
		sleep(1);
		if(b==5)break;
	}
	return NULL;
}
int main()
{
	int i=0;
	pthread_t th1,th2;
	char *p=(char*)malloc(10);
	pthread_create(&th1,NULL,f1,p);
	pthread_create(&th2,NULL,f2,NULL);
	void *ret;
	pthread_join(th1,&ret);
	printf("%s\n",(char*)ret);
	pthread_join(th2,NULL);
	free(p);
	return 0;
}
