#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
int main()
{
	pid_t i=fork();
	int j;
	if(i>0)
	{
		j=50;
		while(j--)
		{
			printf("father:%d\n",getpid());
			sleep(1);
		}
		int w;
		pid_t wi=wait(&w);
		printf("wait:%d\n",wi);
		if(WIFEXITED(w))
		{
			printf("%d\n",WEXITSTATUS(w));
		}
		else if(WIFSIGNALED(w))
		{
			printf("getsignal:%d\n",WTERMSIG(w));
		}

	}
	else if(i==0)
	{
		j=100;
		while(j--)
		{
			printf("son:%d\n",getpid());
			sleep(1);
		}
		exit(50);
	}
}
