#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
	const char *s1="Hello";
	const char *s2="World!";
	char *p=malloc(strlen(s1)+1);
	if(p!=NULL)
	{
		strcpy(p,s1);
	}
	char *q=malloc(strlen(s1)+strlen(s2)+1);
	if(q!=NULL)
	{
		strcpy(q,p);
		strcat(q,s2);
	}
	free(p);
	p=q;
	puts(q);
	free(q);
	p=q=NULL;
}
