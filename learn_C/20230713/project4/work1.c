#include<stdio.h>
int main(void)
{
	int a,b,t_a,t_b,o_a,o_b,new;
	printf("请输入两个十位数：");
	scanf("%d%d",&a,&b);
	t_a=a/10;
	o_a=a%10;
	t_b=b/10;
	o_b=b%10;
	new=o_a*1000+o_b*100+t_b*10+t_a;
	printf("组合出的数为%d\n",new);
}
