#include<stdio.h>
#include<string.h>
int main()
{
	char a[]="hello world";
	int i,l=strlen(a);
	for(i=0;i<l/2;i++)
	{
		char t;
		t=a[i];
		a[i]=a[l-i-1];
		a[l-i-1]=t;
	}
	puts(a);
}
