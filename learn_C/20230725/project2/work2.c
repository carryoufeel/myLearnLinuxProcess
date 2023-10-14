#include<stdio.h>
#include<stdlib.h>
int fib(int n)
{
	if((1==n)||(n==2))
	{
		return 1;
	}
	else
	{
		
		return fib(n-1)+fib(n-2);
	}
}
void inArray(int n, int i,int *a)
{
	*(a+n)=i;
}
void printArry(int *a,int n)
{
	for(int i=0;i<n;i++)
	{
		printf("%d\t",a[i]);
	}
	putchar(10);
}

int main()
{
	int n=0;
	scanf("%d",&n);
	int *a=calloc(n,sizeof(int));
	for(int i=1;i<=n;++i)
	{
		inArray(i-1,fib(i),a);
	}
	printArry(a,n);
	free(a);
}


