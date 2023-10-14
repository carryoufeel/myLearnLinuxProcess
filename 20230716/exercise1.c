#include<stdio.h>
int main()
{
	int a[]={2,0,20,0,5,0,6,0,3,3,0};
	int l=sizeof(a)/sizeof(a[0]);
	int k=0,i=0,j=0;
	for(j=0;j<l-1;++j)
	{
		for(i=j;i<l;i++)
		{
			if(a[i]>a[j])
			{
				k=a[i];
				a[i]=a[j];
				a[j]=k;
			}
		}
	}
	for(i=0;i<l;i++)
	{
		printf("%d\t",a[i]);
	}
	putchar(10);
}
