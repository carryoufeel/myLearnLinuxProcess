#include<stdio.h>
int main()
{
	{
		int a[]={1,2,3,4,5,6,7,8,9,10};
		int sum=0,i=0;
		int len=sizeof(a)/sizeof(a[0]);
		for(;i<len;++i)
		{
			sum+=a[i];
		}
		printf("%d",sum);
	}
	putchar(10);
}
