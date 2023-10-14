#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
int main(int argc, char *argv[])

{
    int aaa = 123810923;
    int fd = open("1.txt",O_WRONLY|O_CREAT|O_TRUNC,0666);
    if(-1 == fd)
    {

        fprintf(stderr,"open error");
        return 1;

    }
    char buf[512]="hello,world";
    int ret =  write(fd,buf,strlen(buf));
    printf("fd is %d, write size %d\n",fd,ret);

    close(fd);
    return 0;
}
