#include<stdio.h>
int main()
{
	FILE *p=fopen("2.txt","w");
	char c[100];
	scanf("%s",c);
	fputs(c,p);
	fclose(p);
}
