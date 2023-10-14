#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<unistd.h>
#include<string.h>
int main()
{
	int a=open("1.txt",O_CREAT|O_WRONLY|O_TRUNC,0666);
	if(a==-1)
	{
		fprintf(stderr,"open error\n");
		return 1;
	}
	char s[512]="你好\n";
	write(a,s,strlen(s));
	close(a);
}

