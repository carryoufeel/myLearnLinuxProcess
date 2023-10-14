#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
int fd ;
void handle(int num)
{

    char buf[512]={0};
    read(fd,buf,sizeof(buf));
    printf("fifo:%s\n",buf);


}
int main(int argc, char *argv[])
{
    signal(SIGIO,handle);
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

     fd = open("fifo",O_RDONLY);
    if(-1 == fd)
    {
        perror("open");
        exit(1);
    }

    int flag = fcntl(fd,F_GETFL);
    fcntl(fd,F_SETFL,flag| O_ASYNC);

    //写管道后，发送SIGIO这个信息，设置信号的接收者
    fcntl(fd,F_SETOWN,getpid());

    while(1)    
    {
        char buf[512]={0};
        fgets(buf,sizeof(buf),stdin);
        printf("terminal:%s",buf);
        fflush(stdout);
    }
    close(fd);
    //remove("fifo");
    return 0;
}
