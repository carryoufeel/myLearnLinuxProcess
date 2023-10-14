#include<stdio.h>
int main()
{
	int a[]={2,3,9,1,4,5,0};
	int l=sizeof(a)/sizeof(a[0]);
	int i,j,k=0;
	for(j=l-1;j>0;--j)
	{
		for(i=0;i<=j-1;i++)
		{
			if(a[i]<a[i+1])
			{
				k=a[i];
				a[i]=a[i+1];
				a[i+1]=k;
			}
		}
	}
	for(i=0;i<l;i++)
	{
		printf("%d\t",a[i]);
	}
	putchar(10);
}
