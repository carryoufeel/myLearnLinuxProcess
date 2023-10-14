#include<stdio.h>
#include<string.h>
int main()
{
	char s[100];
	char k[100];
	gets(s);
	int i=strlen(s),j;
	for(j=0;j<i;j++)
	{
		k[j]=s[j];
		if(s[j]==0)
		{
			break;
		}
	}
	k[j]=0;
	puts(k);
}
