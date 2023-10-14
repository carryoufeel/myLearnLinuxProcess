#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
int main(int argc,char *argv[])
{
	int fd[2];
	int ret=pipe(fd);
	pid_t pid=fork();
	if(pid>0)
	{
		FILE *s=fopen(argv[1],"r");
		close(fd[0]);
		while(1)
		{
			int c=fgetc(s);
			int *a=&c;
			write(fd[1],a,sizeof(c));
			if(c==EOF)
			{
				break;
			}
		}
		fclose(s);
		close(fd[1]);
	}
	else if(pid==0)
	{
		close(fd[1]);
		FILE *d=fopen(argv[2],"w");
		while(1)
		{
			int c;
			int *a=&c;
			int ret=read(fd[0],a,sizeof(c));
			putc(c,d);
			if(ret==0)
			{
				printf("finish\n");
				break;
			}
		}
		close(fd[0]);
		fclose(d);
	}
}
