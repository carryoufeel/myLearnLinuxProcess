#include<stdio.h>
int main()
{
	char s[]="helloworld";
	int i=0;
	int l=sizeof(s)/sizeof(s[0]);
	for(;i<l;i++)
	{
		if(s[i]>'a'&&s[i]<='z')
		{
			s[i]-=32;
		}
	}
	puts(s);
}
