#include<stdio.h>
int main()
{
	int a=123,b,c,d;
	b=a/100;
	c=a%100;
	d=c/10;
	c=c%10;
	printf("%d\n",c*100+d*10+b);
}
