#include<stdio.h>
int main(void)
{
	int a,b,c,max;
	scanf("%d%d%d",&a,&b,&c);
	max=a>b?a:b;
	max=max>c?max:c;
	printf("最大值为：%d\n",max);
}
