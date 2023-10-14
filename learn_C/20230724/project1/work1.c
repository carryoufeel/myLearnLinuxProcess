#include<stdio.h>
void swap(int *a,int *b)

{
	int t=*a;
	*a=*b;
	*b=t;
}
void newBubbleSort(int *begin,int *end)
{
	for(;begin<end;end--)
	{
		for(int *p=begin;p<end;++p)
		{
			if(*p>*(p+1))
			{
				swap(p,p+1);
			}
		}
	}
}
void printArray(int *begin,int *end)
{
	if(begin>end)
	{
		return;
	}
	else
	{
		printf("%d\n",*begin);
		begin++;
		printArray(begin,end);
	}
}
int main()
{
	int a[]={1,4,2,9,3,0,5,6};
	int l=sizeof(a)/sizeof(*a);
	newBubbleSort(a,a+l-1);
	printArray(a,a+l-1);
}
