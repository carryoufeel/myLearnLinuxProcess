#include<stdio.h>
#include<string.h>
int main()
{
	char a[3][100]={"china","hello","world"};
	for(int i=0;i<1;i++)
	{
		char t[100];
		strcpy(t,a[i]);
		strcpy(a[i],a[2-i]);
		strcpy(a[2-i],t);
	}
	for(int i=0;i<3;i++)
	{
		puts(a[i]);
	}
}
