#include<stdio.h>
int main(void)
{
	int c;
	for(c=0;c<100;++c)
	{
		if(c*2+(50-c)*4==140)
		printf("鸡的个数为%d,兔的个数为%d\n",c,50-c);
	}
	return 0;
}
