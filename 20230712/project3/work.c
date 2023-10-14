#include<stdio.h>
int main()
{
	float i = 1.23456789;
	int j=1e6;
	i=i*j;
	printf("%f\n",((int)i/(float)j));	
}
