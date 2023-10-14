#include<stdio.h>
int main(void)
{
	int i,j,k,max;
	scanf("%d%d%d",&i,&j,&k);
	max=i;
	if(max>j)
	{
		max=max;
	}
	else
	{
		max=j;

	}
	if(max>k)
	{
		max=max;
	}
	else
	{
		max=k;
	}
	printf("最大值为%d\n",max);
}
