#include<stdio.h>
#include<string.h>
int main()
{
	char s1[]="Hello";
	char s2[]="World";
	char s3[]="China";
	char max[100];
	strcpy(max,s1);
	if(strcmp(max,s2)<0)
	{
		strcpy(max,s2);
	}
	if(strcmp(max,s3)<0)
	{
		strcpy(max,s3);
	}
	puts(max);
}
