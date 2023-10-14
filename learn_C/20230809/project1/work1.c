#include<stdio.h>
#include<pthread.h>
void *f1(void *arg)
{
	printf("%ld\n",pthread_self());
	pthread_detach(pthread_self());
	return NULL;
}
int main()
{
	pthread_t th1;
	int a=0;
	for(int i=0;i<4000;i++)
	{
		a=pthread_create(&th1,NULL,f1,NULL);
		if(a==0)
		{
			printf("i=%d\n",i);
		}

	}
}
