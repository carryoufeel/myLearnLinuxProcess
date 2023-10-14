#include<stdio.h>
int main()
{
	FILE *p=fopen("1.txt","w+");
	if(p==NULL)
	{
		printf("error\n");
		return 1;
	}
	int a=fputc('H',p);
	if(a==EOF)
	{
		printf("error\n");
		return 1;
	}
	fputc('e',p);
	fputc('l',p);
	fputc('l',p);
	fputc('o',p);
	fputc(10,p);
	fclose(p);
	return 0;
}
