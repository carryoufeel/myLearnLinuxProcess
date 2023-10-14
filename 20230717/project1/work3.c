#include<stdio.h>
int main()
{
	int i,j,n,a[]={1,2,3,4,5,6,9,10,3,6,3,98,10},k=0;
	scanf("%d",&n);
	int l=sizeof(a)/sizeof(a[0]);
	for(i=0;i<l-1;++i)                  
	{                                 
		for(j=i-1;j<l;++j)
		{
			if(a[i]<a[j])             
			{                
				k=a[j];             
				a[j]=a[i];          
				a[i]=k;             
			}
		}
	}
	int mid,begin=0,end=l-1;
	while(begin<=end)
	{
		mid=(begin+end)/2;
		if(a[mid]>n)
		{
			end=mid-1;
		}
		else if(a[mid]<n)
		{
			begin=mid+1;
		}
		else
		{
			break;
		}
	}
	if(begin<=end)
	{
		printf("yes!!!\n");
	}
	else
	{
		printf("no\n");
	}
}
