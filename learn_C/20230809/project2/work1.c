#include<stdio.h>
#include<pthread.h>
pthread_mutex_t lock;
int a=0;
void *f1(void *arg)
{
	int i=10000;
	for(;i>0;i--)
	{
		pthread_mutex_lock(&lock);
		a++;
		printf("%d\n",a);
		pthread_mutex_unlock(&lock);
	}
	return NULL;
}
int main()
{
	pthread_t th1,th2;
	pthread_mutex_init(&lock,NULL);
	pthread_create(&th1,NULL,f1,NULL);
	pthread_create(&th1,NULL,f1,NULL);

	pthread_join(th1,NULL);
	pthread_join(th2,NULL);
	pthread_mutex_destroy(&lock);
}
