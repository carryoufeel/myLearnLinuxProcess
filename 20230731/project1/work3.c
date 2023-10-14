#include<stdio.h>
int main()
{
	FILE *p=fopen("2.txt","w");
	fseek(p,1024*1024*1024,SEEK_SET);
	fputc(1,p);
	fclose(p);
}
