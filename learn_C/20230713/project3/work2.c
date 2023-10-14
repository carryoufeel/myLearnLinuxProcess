#include<stdio.h>
int main()
{
	int a;
	scanf("%d",&a);
	if(a%4==0&&a%100!=0||a%400==0)
	{
		printf("是闰年\n");
	}
	else
	{
		printf("不是闰年\n");
	}
}
