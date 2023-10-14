#include<stdio.h>
void maxOf(int a,int b,int *max)
{
	*max=a;
	if(*max<b)
	{
		*max=b;
	}
}
int main()
{
	int max=0;
	
	maxOf(20,30,&max);
	printf("%d\n",max);
}
