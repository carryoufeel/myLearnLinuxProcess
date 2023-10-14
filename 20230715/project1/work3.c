#include<stdio.h>
int main()
{
	int i,sum=0,k=1;
	for(i=1;i<102;i+=2)
	{
		if(k%2==1)
		{
			sum+=i;
		}
		else
		{
			sum-=i;
		}
		++k;
	}
	printf("%d\n",sum);
}
