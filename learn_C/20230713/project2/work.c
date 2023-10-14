#include<stdio.h>
#include<math.h>
int main(void)
{
	float a,b,c,s,area;
	printf("输入边长：");
	scanf("%f%f%f",&a,&b,&c);
	s=(a+b+c)/2;
	area=sqrt(s*(s-a)*(s-b)*(s-c));
	printf("面积为%f\n",area);
}
