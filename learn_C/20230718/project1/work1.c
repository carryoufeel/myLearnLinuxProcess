#include<stdio.h>
int main()
{
	char s[]="12345";
	int n=0,i=0;
	while(s[i])
	{
		n=s[i]-'0'+n*10;
		i++;
	}
	printf("%d\n",n);
}
