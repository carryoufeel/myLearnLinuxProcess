#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
int main()
{
	int pipfd[2];
	pipe(pipfd);
	pid_t ret=0;
	ret=fork();
	if(ret>0)
	{
		close(pipfd[0]);
		sleep(3);
		char buf[10]="hello";
		write(pipfd[1],buf,strlen(buf)+1);
		close(pipfd[1]);
	}
	else if(ret==0)
	{
		close(pipfd[1]);
		char buf[50]={0};
		read(pipfd[0],buf,sizeof(buf));
		printf("%s\n",buf);
		close(pipfd[0]);
	}
	else
	{
		perror("fork");
		exit(1);
	}
}
