
#include<stdio.h>
void swap(int *a,int *b)
{
	int t=*a;
	*a=*b;
	*b=t;
}
void sort(int *begin,int *end)
{
	int t=*begin;
	int *q=end;
	int *p=begin;
	if(begin>=end)
	{
		return;
	}
	while(p<q)
	{
		while(p<q&&*q>=t)
		{
			--q;
		}
		while(p<q&&*p<=t)
		{
			++p;
		}
		swap(p,q);
	}
	swap(begin,q);
	sort(begin,p-1);
	sort(p+1,end);
}
int *binaryFind(int *begin,int *end,int n)
{
	if(begin>end)
	{
		return NULL;
	}
	else
	{
		int *mid=(end-mid)/2+begin;
		if(*mid>n)
		{
			end=mid-1;
		}
		else if(*mid<n)
		{
			begin=mid+1;
		}
		else
		{
			return mid;
		}
		binaryFind(begin,end,n);
	}
}
int main()
{
	int a[]={2,7,9,0,1,3,5,7,12};
	int l=sizeof(a)/sizeof(*a);
	int n=0;
	scanf("%d",&n);
	sort(a,a+l-1);
	int *i=binaryFind(a,a+l-1,n);
	if(i!=NULL)
	{
		printf("%d\n",*i);
	}
	else
	{
		printf("no\n");
	}
}
