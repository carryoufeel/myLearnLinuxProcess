#include<stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
void handle(int num){};
int main()
{
	signal(SIGCONT,handle);
	int i=10;
	while(i--)
	{
		printf("pid:%d is sleeping\n",getpid());
		sleep(1);
		if(i==5)
		{
			pause();
		}
	}
}
