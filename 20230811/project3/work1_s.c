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
typedef struct sockaddr * (SA);
int main(int argc, char *argv[])
{
    int sockfd = socket(AF_INET,SOCK_DGRAM,0);
    if(-1 == sockfd)
    {
        perror("socket");
        exit(1);
    }
    // man 7 ip
    struct sockaddr_in ser,cli;
    bzero(&ser,sizeof(ser));
    bzero(&cli,sizeof(cli));
    ser.sin_family = AF_INET;
    //把50000 转化为大端
    ser.sin_port  = htons(50000);
    ser.sin_addr.s_addr =  inet_addr("192.168.0.31");
    int ret = bind(sockfd,(SA)&ser,sizeof(ser));
    if(-1 == ret)
    {
        perror("bind");
        exit(1);
    }
    int i =5;
    socklen_t len = sizeof(cli);
    while(i--)
    {   char buf[512]={0};
        recvfrom(sockfd,buf,sizeof(buf),0,(SA)&cli,&len);
        time_t tm;
        time(&tm);
        sprintf(buf,"%s %s",buf,ctime(&tm));
        sendto(sockfd,buf,strlen(buf)+1,0,(SA)&cli,sizeof(cli));
    }

    close(sockfd);
    return 0;
}
