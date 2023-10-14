#include<stdio.h>
int getTheMaxOfArry(int *a,int len)
{
	int max=a[0];
	for(int i=0;i<len;++i)
	{
		if(max<a[i])
		{
			max=a[i];
		}
	}
	return max;
}

void reverse(int *a,int len)
{
	for (int i=0;i<len/2;i++)
	{
		int t=a[i];
		a[i]=a[len-i-1];
		a[len-i-1]=t;
	}
}

void choiceSort(int *a,int len)
{
	for(int i=0;i<len-1;i++)
	{
		for(int j=i;j<len;j++)
		{
			if(a[i]>a[j])
			{
				int t=a[i];
				a[i]=a[j];
				a[j]=t;
			}
		}
	}
}

void bubbleSort(int *a,int len)
{
	int i,j;
	for(j=len-1;j>0;j--)
	{
		for(i=0;i<=j-1;i++)
		{
			if(a[i]<a[i+1])
			{
				int k=a[i];
				a[i]=a[i+1];
				a[i+1]=k;
			}
		}
	}
}

int binaryFind(int *a,int len,int n)
{
	int begin=0;
	int end=len-1;
	int mid=0;
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
		return n;
	}
	else
	{
		return -1;
	}
}

void insertSort(int *a,int len)
{
	for(int i=1;i<len;i++)
	{
		int t=a[i];
		int j=i;
		while(j>0&&a[j-1]>t)
		{
			a[j]=a[j-1];
			--j;
		}
		a[j]=t;
	}
}

void printArry(int *a,int len)
{
	for(int i=0;i<len;i++)
	{
		printf("%d\t",a[i]);
	}
	putchar(10);
}

int main()
{
	int a[10]={1,2,3,4,5,6,7,8,9,0};
	int len=sizeof(a)/sizeof(a[0]);
	int n=0;
	scanf("%d",&n);
	choiceSort(a,len);
//	bubbleSort(a,len);
//	insertSort(a,len);
	printf("%d\n",binaryFind(a,len,n));
//	printf("%d\n",getTheMaxOfArry(a,len));
//	reverse(a,len);
	printArry(a,len);
}

