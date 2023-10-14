#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
int main(int argc,char *argv[])
{
	mkfifo("pip",0666);
	pid_t ret=0; 
	ret=fork();
	if(ret>0)
	{
		FILE *s=fopen(argv[1],"r");
		FILE *p=fopen("pip","w");
		while(1)
		{
			int c=fgetc(s);
			putc(c,p);
			if(c==EOF)
			{
				break;
			}
		}
		fclose(p);
		fclose(s);
	}
	else if(ret==0)
	{
		FILE *d=fopen(argv[2],"w");
		FILE *p=fopen("pip","r");
		while(1)
		{
			int c=fgetc(p);
			putc(c,d);
			if(c==EOF)
			{
				break;
			}
		}
		fclose(p);
		fclose(d);
	}
	remove("pip");
}
