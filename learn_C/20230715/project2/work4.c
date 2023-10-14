#include<stdio.h>
int main()
{
	int a[]={2,3,4,5,6,7};
	int l=sizeof(a)/sizeof(a[0]),i,b;
	for(i=0;i<l/2;++i)
	{
		b=a[i];
		a[i]=a[l-i-1];
		a[l-i-1]=b;
	}
	for(i=0;i<l;++i)
	{
		printf("%d\t",a[i]);
	}
	putchar(10);
}
