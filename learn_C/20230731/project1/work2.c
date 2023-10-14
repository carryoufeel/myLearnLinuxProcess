#include<stdio.h>
#include<string.h>
int main()
{
	FILE *p=fopen("1.txt","r");
	char c[512];
	fseek(p,10,SEEK_SET);
	fgets(c,sizeof(c),p);
	puts(c);
	fclose(p);
}
