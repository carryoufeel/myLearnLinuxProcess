#include<stdio.h>
int main()
{
	int i=0Xffffffff;
	int j=0xB6DE6DB7;
	int a=0x0;
	int b=0b00000000000000100000000000010000; 
	i=i&j;
	a=a|b;
	printf("%x\n",i);
	printf("%x\n",a);
}
