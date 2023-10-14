#include<stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<string.h>
#include<stdlib.h>
int main(int argc,const char *argv[])
{
	int a=open(argv[1],O_RDONLY);
	int b=open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,0666);
	FILE *p=fopen(argv[1],"r");
	fseek(p,0,SEEK_END);
	if(a==-1||b==-1)
	{
		fprintf(stderr,"can't open\n");
		return 1;
	}
	long l=ftell(p);
	char *s=(char*)malloc(1024*1024*10);
	int i=0;
	while(1)
	{
		int ret=read(a,s,sizeof(s));
		if(ret<=0)
		{
			break;
		}
		write(b,s,ret);
	}
	fclose(p);
	close(a);
	close(b);
	free(s);
}
