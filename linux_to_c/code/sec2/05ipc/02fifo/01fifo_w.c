#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
int main(int argc, char *argv[])
{
    int ret = mkfifo("fifo",0666);    
    if(-1 == ret)
    {
        if(EEXIST==errno)
        {

        }
        else
        {
            perror("mkfifo");
            exit(1);
        }
    }

    int fd = open("fifo",O_WRONLY);
    if(-1 == fd)
    {
        perror("open");
        exit(1);
    }
    
    char buf[512]="hello,fifo";
    write(fd,buf,strlen(buf)+1);
    close(fd);
    return 0;
}
