#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<signal.h>
int main()
{
	mkfifo("cheat1",0666);
	mkfifo("cheat2",0666);
	pid_t ret=fork();
	if(ret>0)
	{
		FILE *w=fopen("cheat1","w");
		while(1)
		{
			char buf1[1024]={0};
			//scanf("%s",buf1);
			printf("A:");
			fgets(buf1,sizeof(buf1),stdin);
			fflush(stdin);
			if(strncmp("quit",buf1,4)==0)
			{
				kill(ret,SIGKILL);
				kill(getpid(),SIGKILL);
				break;
			}
			fwrite(buf1,strlen(buf1)+1,1,w);
			fflush(w);
		}
		fclose(w);
	}
	else if(ret==0)
	{
		FILE *r=fopen("cheat2","r");
		while(1)
		{
			char buf2[1024]={0};
			fread(buf2,100,1,r);
			printf("B:%s",buf2);
			fflush(stdout);
			if(strncmp("quit",buf2,4)==0)
			{
				kill(getppid(),SIGKILL);
				kill(getpid(),SIGKILL);
				break;
			}

		}
		fclose(r);
	}
	remove("cheat1");
}
