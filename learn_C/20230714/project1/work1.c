#include<stdio.h>
int main(void)
{
	char a;
	a=getchar();
	if(a<='v')
	{
		a+=5;
	}
	else
	{
		a=a-26+5;
	}
	putchar(a);
	putchar(10);
}
