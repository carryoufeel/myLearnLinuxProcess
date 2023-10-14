#include<stdio.h>
#include<string.h>
int main()
{
	char a[100]="Hello";
	char b[100]="world";
	int i=0,j=0;
	while(a[i]!=0)
	{
		++i;
	}
	while(b[j]!=0)
	{
		a[i]=b[j];
		++j;++i;
	}
	a[i]=0;
	puts(a);
}
