#include<stdio.h>
int main()
{
	int a[]={8,9,10,7,4,1,6,3,9,2};
	int l=20;
	int b[]={4,3,11,6,3,4,2,5,1,0};
	int c[20]={0},i=0,j=0,k=0;
	for(i=0;i<20;i++)
	{
		if(i<10)
		{
			c[i]=a[i];
		}
		else
		{
			c[i]=b[i-10];
		}
	}
	for(j=l-1;j>0;--j)
	{
		for(i=0;i<j;++i)
		{
			if(c[i]>c[i+1])
			{
				k=c[i];
				c[i]=c[i+1];
				c[i+1]=k;
			}
		}
	}
	for(i=0;i<l;i++)
	{
		printf("%d\t",c[i]);
	}
	putchar(10);
}


