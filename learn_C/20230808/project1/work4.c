#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
int a=10;
int b=10;
void *f1(void *arg)
{
	//(int)*(arg+1)=1;
	while(1)
	{
		printf("i'm f1:%ld\n",pthread_self());
		a++;
		printf("f1 value:%d\n",a);
		sleep(1);
		if(a==15)
		{
			break;
		}
	}
	static char s[]="f1,死\n";
	pthread_exit(s);
}
void *f2(void *arg)
{
	//arg+2=2;
	while(1)
	{
		printf("i'm f2:%ld\n",pthread_self());
		b--;
		printf("f2 value:%d\n",b);
		sleep(1);
		if(b==0)
		{
			break;
		}
	}
	static char c[]="f2,死\n";
	pthread_exit(c);
}
int main()
{
	int i=0;
	pthread_t th1,th2;
	int *p=malloc(10);
	pthread_create(&th1,NULL,f1,p);
	pthread_create(&th2,NULL,f2,p);
	free(p);
	void* ret1;
	void* ret2;
	pthread_join(th1,&ret1);
	pthread_join(th2,&ret2);
	printf("%s\n",(char *)ret1);
	printf("%s\n",(char *)ret2);
	return 0;
}
