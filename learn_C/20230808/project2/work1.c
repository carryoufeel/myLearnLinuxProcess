#include<stdio.h>
#include <pthread.h>
void *f1(void *arg)
{
	printf("i'm f1,id:%ld\n",pthread_self());
	return NULL;
}
void *f2(void *arg)
{
	printf("i'm f2,id:%ld\n",pthread_self());
	return NULL;
}
void *f3(void *arg)
{
	printf("i'm f3,id:%ld\n",pthread_self());
	return NULL;
}
void *f4(void *arg)
{
	printf("i'm f4,id:%ld\n",pthread_self());
	return NULL;
}
void *f5(void *arg)
{
	printf("i'm f5,id:%ld\n",pthread_self());
	return NULL;
}
int main()
{
	int c;
	pthread_t a1;
	pthread_t a2;
	pthread_t a3;
	pthread_t a4;
	pthread_t a5;
	void (*b[5])={f1,f2,f3,f4,f5};
	pthread_t a[5]={a1,a2,a3,a4,a5};
	for(int i=0;i<5;i++)
	{
		pthread_create(&a[i],NULL,b[i],NULL);
		pthread_join(a[i],NULL);
	}
}
