#include<stdio.h>
int main(void)
{
	int j,i=0;
	for(j=0;j<1000;j++)
	{
		
		if(j%2==1&&j%3==1&&j%5==1)
		{
			printf("%d\t",j);
			++i;
		}
		if(i==10)
		{
			break;
		}
	}
	putchar(10);
}
