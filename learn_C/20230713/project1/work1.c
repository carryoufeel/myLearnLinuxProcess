#include<stdio.h>
int main(void)
{
	float r,pi=3.14,c,s;
	scanf("%f",&r);
	c=2*pi*r;
	s=pi*r*r;
	printf("周长为：%f,面积为：%f\n",c,s);
}
