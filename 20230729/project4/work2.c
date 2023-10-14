#include<stdio.h>
int main(int argc,char *argv[])
{
	if(argc<=2)
	{
		printf("no\n");
		return 1;
	}
	char buff[1024]={0};
	FILE *s=fopen(argv[1],"r");
	FILE *d=fopen(argv[2],"w");
	if(NULL==s&&NULL==d)
	{
		printf("can't open\n");
		return 1;
	}
	fread(buff,1024,1,s);
	fwrite(buff,1024,1,d);
	fclose(s);
	fclose(d);
}
