#include<stdio.h>
union Demo
{
	char c;
	int i;
};
int main(void)
{
	union Demo d;
	d.c=1;
	if(d.i==1)
	{
		printf("小段\n");
	}
	else
	{
		printf("大段\n");
	}
}
