#include<stdio.h>
int ohMyPrimeNumber(int a)
{
	int i;
	for(i=a-1;i>1;--i)
	{
		if(a%i==0)
		{
			return 0;
		}
	}
	return 1;
}
void printfMyPrimeNumber(int begin,int end)
{
	int n=0;
	for(int i=begin;i<=end;i++)
	{
		if(ohMyPrimeNumber(i)&&ohMyPrimeNumber(i+2))
		{
			printf("%d %d\t",i,i+2);
			n++;
			//getArry(i,n);
		}
	}
	putchar(10);
}

void getArry(int i,int n)
{
	int a[n];
	for(int j=0;j<n;j++)
	{
		a[j]=i;
	}
	printArry(a,n);
}

void printArry(int *a,int len)
{
	for(int i=0;i<len;i++)
	{
		printf("%d\n",a[i]);
	}
	putchar(10);
}

int main()
{
	int a,b;
	scanf("%d%d",&a,&b);
	printfMyPrimeNumber(a,b);
	
}
