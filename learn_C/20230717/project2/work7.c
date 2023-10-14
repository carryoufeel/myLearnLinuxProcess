#include<stdio.h>
int main()
{
	char s1[100]="Hello";
	char s2[100]="World";
	int a=0,i=0;
	while(s1[i]==s2[i]&&s1[i]!=0&&s2[i]!=0)
	{
		++i;
	}
	a=s1[i]-s2[i];
	printf("%d\n",a);
}
