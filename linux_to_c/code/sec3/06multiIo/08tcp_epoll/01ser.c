
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <time.h>
/* According to POSIX.1-2001, POSIX.1-2008 */
#include <sys/select.h>

/* According to earlier standards */
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/epoll.h>

typedef struct sockaddr * (SA);
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

int del_fd(int epfd,int fd )
{
    struct epoll_event ev;
    ev.events  = EPOLLIN;
    ev.data.fd = fd;
    int ret = epoll_ctl(epfd,EPOLL_CTL_DEL,fd,&ev);
    if(-1 == ret)
    {
        perror("epoll_ctl");
        return 1;
    }
    return 0;
}
int main(int argc, char *argv[])
{
    //监听套接子
    int listfd = socket(AF_INET,SOCK_STREAM,0);
    if(-1 == listfd)
    {
        perror("socket");
        return 1;
    }
    // man 7 ip
    struct sockaddr_in ser,cli;
    bzero(&ser,sizeof(ser));
    bzero(&cli,sizeof(cli));
    ser.sin_family = AF_INET;
    //把50000 转化为大端
    ser.sin_port  = htons(50000);
    ser.sin_addr.s_addr =  inet_addr("127.0.0.1");

    int ret = bind(listfd,(SA)&ser,sizeof(ser));
    if(-1 == ret)
    {
        perror("bind");
        return 1;
    }
    listen(listfd,3);
    socklen_t len = sizeof(cli);

    struct epoll_event rev[10];
    int epfd = epoll_create(10);
    if(-1 == epfd)
    {
        perror("epoll_create");
        return 1;
    }

    add_fd(epfd,listfd);

    while(1)
    {

        char buf[1024]={0};
        int i = 0 ;
        int ep_ret = epoll_wait(epfd,rev,10,-1);

        //通信套接子
        for(i=0;i<ep_ret;i++)
        {
           // if(FD_ISSET(i,&rd_set) && i == listfd)
            if(rev[i].data.fd == listfd)
            {
                int conn =accept(listfd,(SA)&cli,&len);
                if(-1 == conn)
                {
                    perror("accept");
                    continue;
                }

                add_fd(epfd,conn);
            }
            //if(FD_ISSET(i,&rd_set) && i!=listfd)
            else 
            {
                int conn = rev[i].data.fd;
                int rd_ret = recv(conn,buf,sizeof(buf),0);
                if(rd_ret<=0)
                {

                    del_fd(epfd,conn);
                    close(conn);
                    printf("cli offline\n");
                    continue;
                }
                time_t tm;
                time(&tm);
                sprintf(buf,"%s %s",buf,ctime(&tm));
                send(conn,buf,strlen(buf)+1,0);
            }
        }
    }

    close(listfd);
    return 0;
}
