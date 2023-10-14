#include<stdio.h>
int main(int argc,char *argv[])
{
	if(argc<=2)
	{
		printf("no\n");
		return 1;
	}
	FILE *s=fopen(argv[1],"r");
	FILE *d=fopen(argv[2],"w");
	if(NULL==s)
	{
		printf("can't open\n");
		return 1;
	}
	while(1)
	{
		int c=fgetc(s);
		putc(c,d);
		if(c==EOF)
		{
			break;
		}
	}
	fclose(d);
	fclose(s);
}
