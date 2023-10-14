#include<stdio.h>
void maxOfArray(int *a,int l,int *max)
{
	int i=0;
	*max=*(a+i);
	for(i=0;i<l;i++)
	{
		if(*max<*(a+i))
		{
			*max=*(a+i);
		}
	}
}

void swap(int *a,int *b)
{
	int t=*a;
	*a=*b;
	*b=t;
}

void reverseOfArray(int *a,int l)
{
	for(int i=0;i<l/2;i++)
	{
		swap(a+i,a+l-i-1);
	}
	//*a=a[0];
}

void ohMySort(int *a,int l)
{
	for(int i=0;i<l-1;i++)
	{
		for(int j=i;j<l;j++)
			if(*(a+i)>*(a+j))
			{
				swap(a+i,a+j);
			}
	}
}

void printArray(int *a,int l)
{
	for(int i=0;i<l;i++)
	{
		printf("%d\t",*(a+i));
	}
	putchar(10);
}

void binaryFind(int *a,int l,int *n)
{
	int begin=0,end=l-1;
	int mid;
	while(begin<=end)
	{
		mid=(begin+end)/2;
		if(*(a+mid)>*n)
		{
			end=mid-1;
		}
		else if(*(a+mid)<*n)
		{
			begin=mid+1;
		}
		else
		{
			break;
		}
		if(begin<=end)
		{
			*n=mid;
		}
		else
		{
			*n=-1;
		}
	}
}

void newReverse(int *begin,int *end)
{
	while(begin<=end)
	{
		swap(begin++,end--);
	}

}

void newRerverseByRecursion(int *begin,int *end)
{
	if(begin>end)
	{
		return;
	}
	else
	{
		swap(begin,end);
		newRerverseByRecursion(begin+1,end-1);
	}
}

void newSort(int *begin,int *end)
{
	for(;begin<end;++begin)
	{
		for(int *p=begin+1;p<=end;++p)
		{
			if(*begin>*p)
			{
				swap(begin,p);
			}
		}
	}
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

void qSort(int *begin,int *end)
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
	qSort(begin,p-1);
	qSort(p+1,end);
}

int *newBarryFind(int *begin,int *end,int n)
{
	while(begin<=end)
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
	}
		return NULL;
}

void newPrintByRecursion(int *begin,int *end)
{
	if(begin>end)
	{
		putchar(10);
		return;
	}
	else
	{
		printf("%d\t",*begin);
		newPrintByRecursion(begin+1,end);
	}
}

void ohMyPrint(int *begin,int *end)
{
	while(begin <= end)
	{
		printf("%d\t",*begin);
		begin++;
	}
	putchar(10);
}

int main()
{
	int a[]={1,2,9,8,4};
	int l=5;
	int max;
	int n=-9;
	int *i;
	//newReverse(a,a+l-1);
	//newSort(a,a+l-1);
	newBubbleSort(a,a+l-1);
	//qSort(a,a+l-1);
	i=newBarryFind(a,a+l-1,n);
	ohMyPrint(a,a+l-1);
	//newRerverseByRecursion(a,a+l-1);
	//newPrintByRecursion(a,a+l-1);
	//scanf("%d",&n);
	//maxOfArray(a,l,&max);
	//printf("%d\n",max);
	printf("%d\n",*i);
	//reverseOfArray(a,l);
	//ohMySort(a,l);
	//printArray(a,l);
	//binaryFind(a,l,&n);
	//printf("%d\n",n);
}
