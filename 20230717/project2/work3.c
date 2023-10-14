#include<stdio.h>
int main()
{
	char s[100];
	gets(s);
	int i;
	for(i=0;i<100;i++)
	{
		if(s[i]==0)
		{
			break;
		}
	}
	printf("%d\n",i);
}
