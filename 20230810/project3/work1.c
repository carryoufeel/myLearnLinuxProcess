#include<stdio.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
int main(int argc,char *argv[])
{
	pid_t pid=atoi(argv[1]);
	int ret=kill(pid,SIGKILL);
	if(-1==ret)
	{
		printf("no\n");
	}
	return 0;
}
