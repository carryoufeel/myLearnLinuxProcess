#include<stdio.h>
int main()
{
	int i=0,j=0;
		for(;j<10;)
		{
			if(i%2==1&&i%3==1&&i%5==1)
			{
				printf("%d\n",i);
				j++;
				i++;
			}
			i++;
		}
}
