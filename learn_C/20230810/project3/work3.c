#include<stdio.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

int main()
{
	int i=0;
	for(;i<10;i++)
	{
		printf("I'm sleeping\n");
		if(i==5)pause();
	}
}
