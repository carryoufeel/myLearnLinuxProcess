#include<stdio.h>
void palidromeNumbr(int n)
{
	for(;n>=0;--n)
	{
		int m=0;
		int k=n;
		while(k!=0)
		{
			m=m*10+k%10;
			k/=10;
		}
		return m == k;
	}
}
int main()
{
	int n=0;
	scanf("%d",&n);
	palidromeNumbr(n);
	putchar(10);
}
