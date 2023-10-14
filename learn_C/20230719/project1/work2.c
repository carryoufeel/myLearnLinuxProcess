#include<stdio.h>
int fn(int n)
{
	if(n==1)
	{
		return 1;
	}
	else
	{
		return fn(n-1)*n;
	}
}
int main()
{
	printf("%d\n",fn(8));
}
