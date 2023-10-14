#include<stdio.h>
int main()
{
	int a[]={1,2,3,4,5,6,7,8,9,10};
	int l=sizeof(a)/sizeof(a[0]),i=0;
	for(;i<l;++i)
	{
		if(a[i]%3==0)
			printf("%d\t",a[i]);
	}
	putchar(10);
}
