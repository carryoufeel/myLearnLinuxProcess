#include<stdio.h>
int main()
{
	int a[3][4]={1,2,3,4,5,6,7,8,9,10,11,12};
	int sum=0,i,j;
	int row=sizeof(a)/sizeof(a[0]);
	int cols=sizeof(a[0])/sizeof(a[0][0]);
	for(i=0;i<row;++i)
	{
		for(j=0;j<cols;++j)
		{
			sum+=a[i][j];
		}
	}
	printf("%d\n",sum);
}
