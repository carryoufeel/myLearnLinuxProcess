#include<stdio.h>
int main()
{
	int a[3][4]={1,2,3,4,5,6,7,8,9,10,11,12};
	int row=sizeof(a)/sizeof(a[0]),
	    cols=sizeof(a[0])/sizeof(a[0][0]);
	for(int i=0;i<row;++i)
	{
		for(int j=0;j<cols/2;++j)
		{
			int t=a[i][j];
			a[i][j]=a[i][cols-j-1];
			a[i][cols-j-1]=t;
		}
	}
	for(int i=0;i<row;++i)
	{
		for(int j=0;j<cols;++j)
		{
			printf("%d\t",a[i][j]);
		}
		putchar(10);
	}
}
