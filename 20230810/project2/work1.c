#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<string.h>
#include<unistd.h>
int main()
{
	mkfifo("fifo",0666);
	int f=open("fifo",O_WRONLY);
	char buf[512]="hello\n";
	write(f,buf,strlen(buf)+1);
	close(f);
}
