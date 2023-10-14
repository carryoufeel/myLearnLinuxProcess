#include<stdio.h>
int summationOfArrayDiagonals(int a[][4],int rows)
{
	int i,sum=0,j=0;
	for(i=0;i<3;i++)
	{
		for(j=0;j<rows;j++)
		{
			if(i==j)
			{
				sum+=a[i][j];
			}
		}
	}
}
void printArray2DTran(int a[][4],int rows)
{
	int i,j;
	int cols=sizeof(a[0])/sizeof(a[0][0]);
	for(i=0;i<cols;i++)
	{
		for(j=0;j<rows;j++)
		{
			printf("%2d",a[j][i]);
		}
		putchar(10);
	}
}
int print2DArray(int a[][4],int rows)
{
	int i,j;
	int cols=sizeof(a[0])/sizeof(a[0][0]);
		for()
}
int main()
{
	//int a[3][3]={1,2,3,4,5,6,7,8,9};
	int a[][4]={1,2,3,4,5,6,7,8,9,10,11,12};
	int rows=sizeof(a)/sizeof(a[0]);
	printf("%d\n",summationOfArrayDiagonals(a,rows));
	printArray2DTran(a,rows);
}
