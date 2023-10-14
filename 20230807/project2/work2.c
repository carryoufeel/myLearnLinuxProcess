#include<stdio.h>
#include<unistd.h>
#include <stdlib.h>
int main(int argc,char *argv[])
{
	int n=0;
	scanf("%d",&n);
	switch(n)
	{
	case 1:
		execlp("/usr/bin/firefox","firefox",NULL);
		break;
	case 2:
		execlp("/usr/bin/gnome-calculator","gnome-calculator",NULL);
		break;
	case 3:
		execlp("/usr/bin/file","file",NULL);
		break;
	case 4:
		exit(1);
		break;
	}
}
