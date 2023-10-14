#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<stdio.h>
#include <unistd.h>
int main()
{
	int a=open("1.txt",O_RDONLY);
	if(a==-1)
	{
		fprintf(stderr,"can't open");
	}
	char s[512];
	read(a,s,sizeof(s));
	printf("%s\n",s);
}

