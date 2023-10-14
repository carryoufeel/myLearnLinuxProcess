#include<stdio.h>
int main()
{
	int i,j,a[]={9,8,10,4,2,7,10,38,89,12},k;
	int l=sizeof(a)/sizeof(a[0]);
	for(j=l-1;j>0;--j)
	{
		for(i=0;i<j;++i)                   //j用来控制i的取值范围，每轮让i少跑一个
		{
			if(a[i]>a[i+1])
			{  								//相邻的元素比较，小的放前，大的放后
				k=a[i];                     //与选择排序不同，冒泡排序是两个数同时移动
				a[i]=a[i+1];
				a[i+1]=k;
			}
		}
	}
	for(i=0;i<l;i++)
	{
		printf("%d\t",a[i]);
	}
	putchar(10);
}
