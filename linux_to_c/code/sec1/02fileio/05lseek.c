#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/types.h>
#include <unistd.h>
#include <string.h>
int main(int argc, char *argv[])

{
    int fd = open("1.txt",O_WRONLY);
    if(-1 == fd)
    {
    
        fprintf(stderr,"open error");
        return 1;
        
    }
    int ret = lseek(fd,5,SEEK_SET);
    if(-1 == ret)
    {
        fprintf(stderr,"lseek error");
        return 1;
    }

    char buf[]="hello,";
    //fputs(buf,(int)fp);
    //
    write(fd,buf,strlen(buf));
    close(fd);
    return 0;
}
