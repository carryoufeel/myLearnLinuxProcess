#include<stdio.h>
int main()
{
	int a[]={9,3,0,1,4,8};
	int l=sizeof(a)/sizeof(a[0]);
	int i,j;
	int b[l];
	b[0]=a[0];		//第一个数放入新数组
	for(i=1;i<l;i++)
	{
		int t=a[i];
		int j=i;//要先把数放进不同数组的相同位置
		while(j>0&&b[j-1]>t)//如果前面的数比后面的数大
		{
			b[j]=b[j-1];//把前面的数复制一份
			--j;//位置向前移一个
		}
		b[j]=t;//如果前面的数每后面的数大，则直接赋值
	}
	for(i=0;i<l;i++)
	{
		a[i]=b[i];
	}
	for(i=0;i<l;i++)
	{
		printf("%d\t",a[i]);
	}
	putchar(10);
}
