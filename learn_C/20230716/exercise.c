#include<stdio.h>
int main()
{
	int a[]={1,2,3,4};
	int l=sizeof(a)/sizeof(a[0]);
	int i=0,k=0;
	for (;i<l/2;++i)
	{
		k=a[i];
		a[i]=a[l-i-1];
		a[l-i-1]=k;
	}
	for(i=0;i<l;i++)
	{
		printf("%d\t",a[i]);
	}
	putchar(10);

}
