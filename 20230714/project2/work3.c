#include<stdio.h>
#include<math.h>
int main(void)
{
	float a,b,c,x1,x2,deta,i=0.0;
	printf("输入一元二次方程的abc的值：\n");
	scanf("%f%f%f",&a,&b,&c);
	deta=pow(b,2)-4*a*c;
	if(deta<0)
	{
		i=-1.0;
	}
	else if(0==deta)
	{
		x1=x2=(-b)/(2.0*a);
	}
	else
	{
		x1=(-b+sqrt(deta))/(2.0*a);
		x2=(-b-sqrt(deta))/(2.0*a);
	}
	if(i<0)
	{
		printf("无实根\n");
	}
	else if(x1==x2)
	{
		printf("有两个相同的根%f\n",x1);
	}
	else
	{
		printf("有两个不同的实根，分别是%f,%f\n",x1,x2);
	}
	return 0;
}
