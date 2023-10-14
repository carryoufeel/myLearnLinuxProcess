#include<stdio.h>
int main()
{
	int a[3][4]={1,2,3,4,5,6,7,8,9,10,11,12};
	int sum=0,i,j;
	for(i=0;i<3;i++)
	{
		for(j=0;j<4;j++)
		{
			if(0==i||0==j||2==i||3==j)
			{
				sum+=a[i][j];
			}
		}
	}
	printf("%d\n",sum);
}
