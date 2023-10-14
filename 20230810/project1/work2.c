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
		//sleep(3);
		char buf[1024]="0";
		for(int i=0;i<66;i++)
		{
			write(pipfd[1],buf,sizeof(buf));
			printf("i=%d\n",i);
		}
		close(pipfd[1]);
	}
	else if(ret==0)
	{
		close(pipfd[1]);
		char buf[1024]={0};
		sleep(2);
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
