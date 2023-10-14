#include<stdio.h>
#include<unistd.h>
int main()
{
	execl("/usr/bin/firefox","firefox","ys.mihoyo.com",NULL);
	printf("看见就错了\n");
	return 0;
}
