#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
void myhandle1(int num)
{
	static int i=0;
	printf("狗叫\n");
	if(3==i)
	{
		signal(SIGINT,SIG_IGN);
	}
	i++;
}
void myhandle2(int num)
{
	static int i=0;
	printf("死了\n");
	if(3==i)
	{
		signal(SIGQUIT,SIG_DFL);
	}
	i++;
}

int main()
{
	signal(SIGINT,myhandle1);
	signal(SIGQUIT,myhandle2);
	while(1)
	{
		printf("i'm playing\n");
		sleep(1);
	}
}
