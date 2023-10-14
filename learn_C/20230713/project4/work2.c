#include<stdio.h>
int main(void)
{
	char a;
	a=getchar();
	if(a<=57&&a>=48)
	{
		printf("是数字\n");
	}
	else if(a<=90&&a>=65)
	{
		printf("是大写字母\n");
	}
	else if(a<=122&&a>=97)
	{
		printf("是小写字母\n");
	}
	else
	{
		printf("是其他字符\n");
	}
}
