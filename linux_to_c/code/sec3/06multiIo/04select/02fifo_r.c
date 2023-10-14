#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
/* According to POSIX.1-2001, POSIX.1-2008 */
#include <sys/select.h>

/* According to earlier standards */
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
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

    int fd = open("fifo",O_RDONLY);
    if(-1 == fd)
    {
        perror("open");
        exit(1);
    }

    fd_set rd_set,tmp_set;
    FD_ZERO(&rd_set);
    FD_ZERO(&tmp_set);

    FD_SET(fd,&tmp_set);
    FD_SET(0,&tmp_set);

    char buf[512]={0};
    while(1)    
    {
        rd_set = tmp_set;
        select(fd+1,&rd_set,NULL,NULL,NULL);
        if(FD_ISSET(fd,&rd_set))
        {
            read(fd,buf,sizeof(buf));
            printf("fifo:%s\n",buf);
        }

        if(FD_ISSET(0,&rd_set))
        {
            bzero(buf,sizeof(buf));
            fgets(buf,sizeof(buf),stdin);
            printf("terminal:%s",buf);
            fflush(stdout);
        }
    }
    close(fd);
    //remove("fifo");
    return 0;
}
