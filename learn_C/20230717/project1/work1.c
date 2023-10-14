#include<stdio.h>
int main()
{
	int a[]={2,6,8,5,7,1};
	int l=sizeof(a)/sizeof(a[0]);
	int i=1;
	for(;i<l;i++)
	{
		int t=a[i];
		int j=i;
		while(j>0&&a[j-1]>t)
		{
			a[j]=a[j-1];
			--j;
		}
		a[j]=t;
	}
	for(i=0;i<l;++i)
	{
		printf("%d\t",a[i]);
	}
	putchar(10);
}
