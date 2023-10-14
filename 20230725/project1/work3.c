#include<stdio.h>
#include<string.h>
char *Strcat(char *dest,const char *scr)
{
	char *ret=dest;
	while(*dest)
	{
		dest++;
	}
	while(*scr)
	{
		*dest++=*scr++;
	}
	*dest=0;
	return ret;
}

int main()
{
	char s[100]="Hello";
	puts(Strcat(s,"china"));
}
