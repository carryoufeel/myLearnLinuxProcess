#include<stdio.h>
int maxOfThreeNumbers(int a,int b,int c)
{
	int i=a;
	if(b>i)
	{
		i=b;
	}
	else
	{
		i=i;
	}
	if(c>i)
	{
		i=c;
	}
	else
	{
		i=i;
	}
	return i;
}

int main()
{
	printf("%d\n",maxOfThreeNumbers(10,20,30));
}
