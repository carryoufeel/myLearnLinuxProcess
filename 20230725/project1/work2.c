#include<stdio.h>
void printArray2D(int (*a)[4],int rows)
{
	int i,j;
	int cols=sizeof(*a)/sizeof(**a);
	for(i=0;i<rows;++i)
	{
		for(j=0;j<cols;++j)
		{
			printf("%d\t",*(*(a+i)+j));
		}
		putchar(10);
	}
}

int findMax(int (*a)[4],int rows)
{
	int i,j;
	int cols=sizeof(*a)/sizeof(**a);
	int max=**a;
	for(i=0;i<rows;++i)
	{
		for(j=0;j<cols;++j)
		{
			if(max<*(*(a+i)+j))
			{
				max=*(*(a+i)+j);
			}
		}
	}
	return max;
}
void ave(int (*a)[4],int rows,float *result)
{
	int i,j;
	int cols=sizeof(*a)/sizeof(**a);
	float sum=0;
	for(i=0;i<rows;++i)
	{
		for(j=0;j<cols;++j)
		{
			sum=sum+*(*(a+i)+j);
		}
		sum=sum/4.0;
		*(result+i)=sum;
		sum=0;
	}
}
int main()
{
	int a[3][4]={1,2,3,4,5,6,7,8,9,10,11,12};
	float result[3];
	ave(a,3,result);
	printf("%d\n",findMax(a,3));
	printArray2D(a,3);
	for(int i=0;i<3;i++)
	{
		printf("%f\n",result[i]);
	}
}
