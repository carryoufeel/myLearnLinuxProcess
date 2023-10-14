#include<stdio.h>
int main()
{
	int n,m=0,k;
	scanf("%d",&n);
	k=n;
	while(k!=0)
	{
		m=m*10+k%10;
		k/=10;
	}
	if(n==m)
	{
		printf("%d是回文数\n",m);
	}
	else
	{
		printf("%d不是回文数\n",n);
	}
}
