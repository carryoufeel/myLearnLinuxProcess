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
#include <sys/epoll.h>
int add_fd(int epfd,int fd )
{

    struct epoll_event ev;
    ev.events  = EPOLLIN;
    ev.data.fd = fd;
    int ret = epoll_ctl(epfd,EPOLL_CTL_ADD,fd,&ev);
    if(-1 == ret)
    {
        perror("epoll_ctl");
        return 1;
    }
    return 0;
}
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
    
    struct epoll_event rev[2];
    int epfd = epoll_create(2);
    if(-1 == epfd)
    {
        perror("epoll_create");
        return 1;
    }
    add_fd(epfd,0);
    add_fd(epfd,fd);
    int i = 0 ;
    while(1)    
    {
        char buf[1024]={0};
        int ep_ret = epoll_wait(epfd,rev,2,-1);

        for(i = 0 ;i<ep_ret;i++)
        {
            if(rev[i].data.fd == fd)
            {
                read(fd,buf,sizeof(buf));
                printf("fifo:%s\n",buf);
            }

            if(0 == rev[i].data.fd )
            {
                bzero(buf,sizeof(buf));
                fgets(buf,sizeof(buf),stdin);
                printf("terminal:%s",buf);
                fflush(stdout);
            }
        }
    }
    close(fd);
    //remove("fifo");
    return 0;
}
