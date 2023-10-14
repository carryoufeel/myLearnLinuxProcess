#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<string.h>
#include<unistd.h>
int main()
{
	mkfifo("fifo",0666);
	int f=open("fifo",O_RDONLY);
	char buf[512]="0";
	read(f,buf,sizeof(buf));
	printf("%s",buf);
	close(f);
	remove("fifo");
}
