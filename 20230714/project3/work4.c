#include<stdio.h>
int main()
{
	int i;
	for(i=0;i<=10000;++i)
	{
		int m=0;
		int k=i;
		while(k!=0)
		{
			m=m*10+k%10;
			k/=10;
		}
		if(m==i)
		{
			printf("%d\t",i);
		}
	}
	printf("\n");
}
