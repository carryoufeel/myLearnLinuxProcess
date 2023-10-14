#include<stdio.h>
int main()
{
	int n=1,i;
	for(;n<100;++n)
	{
		for(i=2;i<n;i++)
		{
			if(n%i==0)
			{
				break;
			}
		}
		if(i<n){}
		else
		{
			printf("%d\t",n);
		}
	}
	putchar(10);
}
