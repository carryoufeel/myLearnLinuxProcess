#include<stdio.h>
int main()
{
	int a[]={1,2,3,4,5,6,7,8,9},n=0;
	int l=sizeof(a)/sizeof(a[0]);
	int t=0,i=0;
	scanf("%d",&n);
	for(;i<n;i++)
	{
		t=a[l-1];
		for(int j=l-1;j>=0;j--)
		{
			a[j+1]=a[j];
		}
		a[0]=t;
	}
	for(i=0;i<l;i++)
	{
		printf("%d\t",a[i]);
	}
	putchar(10);
}
