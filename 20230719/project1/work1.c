#include<stdio.h>
int isPrimeNumber(int n)
{
	int i=n;
	for(n=n-1;n>1;--n)
	{
		if(i%n==0)
		{
			return 0;
		}
	}
	return 1;
}
void printPrimeNumber(int begin,int end)
{
	int n;
	for(n=begin;n<=end;n++)
	{
		if(isPrimeNumber(n))
		{
			printf("%d\t",n);
		}
	}
}
int main()
{
	int i,j;
	scanf("%d%d",&i,&j);
	printPrimeNumber(i,j);
	putchar(10);
}
