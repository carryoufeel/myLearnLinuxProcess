#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
int main()
{
	pid_t i=fork();
	int j;
	if(i>0)
	{
		j=5;
		while(j--)
		{
			printf("father:%d\n",getpid());
			sleep(1);
		}
		int w;
		pid_t wi=wait(&w);
		printf("wait:%d\n",wi);
	}
	else if(i==0)
	{
		j=10;
		while(j--)
		{
			printf("son:%d\n",getpid());
			sleep(1);
		}
	}
}
