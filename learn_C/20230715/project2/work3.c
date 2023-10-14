#include<stdio.h>
int main()
{
	int a[]={1,2,3,4,5,6};
	int max=a[0],i;
	int l=sizeof(a)/sizeof(a[0]);
	for(i=1;i<l;i++)
	{
		if(max<a[i])
		{
			max=a[i];
		}
	}
	int max1=0x80000000;
	for(i=1;i<l;i++)
	{
		if(max1<a[i]&&a[i]!=max)
		{
			max1=a[i];
		}

	}
	printf("%d\n",max1);
}
