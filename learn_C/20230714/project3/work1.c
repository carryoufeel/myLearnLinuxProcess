#include<stdio.h>
int main(void)
{
	int i=0,j=0;
	for(;i<=100;++i)
	{
		if(i%3==0)
		{
			printf("%d\t",i);
			++j;
		}
	}
	printf("\n一共有%d个数能被三整除\n",j);
	return 0;
}
