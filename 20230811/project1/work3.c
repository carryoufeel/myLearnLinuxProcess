#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
void myhandle(int num)
{
	if(SIGUSR1==num)
	{
		static int i=0;
		printf("去死\n");
		if(i==3)
		{
			signal(SIGUSR1,SIG_IGN);
		}
		i++;
	}
	else if(SIGUSR2==num)
	{
		static int j=0;
		printf("你什么时候死\n");
		if(4==j)
		{
			signal(SIGUSR2,SIG_DFL);
		}
		j++;
	}
}
int main()
{
	signal(SIGUSR1,myhandle);
	signal(SIGUSR2,myhandle);
	while(1)
	{
		printf("i'm play,%d\n",getpid());
		sleep(1);
	}
}
