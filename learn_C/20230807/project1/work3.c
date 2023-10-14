#include<stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
	int j=0;
	pid_t a[10]={0};
	for(;j<10;j++)
	{
		a[j]=fork();
		if(a[j]>0)
		{
			int i=2;
			while(i--)
			{
			}
		}
		else if(a[j]==0)
		{
			a[j]=getpid();
			int i=2;
			while(i--)
			{
				printf("child:%d\n",getpid());
				sleep(1);
			}
			exit(10);
		}
		
	}		
	int kellson=3;
	int wstatus;
	while(1)
	{
		pid_t recycle=waitpid(a[kellson],&wstatus,WNOHANG);
		if(a[kellson]==recycle)
		{
			if(WIFEXITED(wstatus))
			{
				printf("回收成功，pid:%d\n",recycle);
			}
			break;
		}
		else if(0==recycle)
		{
			printf("还没杀死\n");
			sleep(1);
		}
	}
}
