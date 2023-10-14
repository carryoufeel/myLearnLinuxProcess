#include<stdio.h>
int main()
{
	int i,j,a[]={1,2,3,4,5,6,9,10,3,6,3,98,10},k=0;
	int l=sizeof(a)/sizeof(a[0]);
	for(i=0;i<l-1;++i)                  //选择排序就是求极值问题
	{                                   //a[i]表示合适的位置，i只能到l-1的地方
		for(j=i-1;j<l;++j)                
		{
			if(a[i]<a[j])             //降序排序a[i]>a[j]是升序排序
			{                         //第一次是把最大的值放在了第一个位置上
				k=a[j];               //以此类推
				a[j]=a[i];            //算法复杂度：n^2
				a[i]=k;               //空间复杂度 
			}
		}
	}
	for(i=0;i<l;i++)
	{
		printf("%d\t",a[i]);
	}
	putchar(10);
}
