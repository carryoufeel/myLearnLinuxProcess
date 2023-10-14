#include<stdio.h>
#include<pthread.h>
typedef struct
{
	float a;
	float b;
	char c;
	float d;
}CALCULATOR;
void *calculator(void *arg)
{
	CALCULATOR* tmp=(CALCULATOR*)arg;
	float *ans=&(tmp->d);
	if(tmp->c=='+')
	{
		*ans=tmp->a+tmp->b;
	}
	else if(tmp->c=='-')
	{
		*ans=tmp->a-tmp->b;
	}
	else if(tmp->c=='*')
	{
		*ans=tmp->a*tmp->b;
	}
	else
	{
		*ans=tmp->a/tmp->b;
	}
	return ans;
}
int main()
{
	pthread_t a;
	CALCULATOR cal;
	printf("符号\n");
	cal.c=getchar();
    printf("a=\n");
	scanf("%f",&cal.a);
	printf("b=\n");
	scanf("%f",&cal.b);
	pthread_create(&a,NULL,calculator,&cal);
	pthread_join(a,NULL);
	printf("答案是%f\n",cal.d);
}

