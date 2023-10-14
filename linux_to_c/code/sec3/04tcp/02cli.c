
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
    //监听套接子
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(-1 == sockfd)
    {
        perror("socket");
        return 1;
    }
    // man 7 ip
    struct sockaddr_in ser;
    bzero(&ser,sizeof(ser));
    ser.sin_family = AF_INET;
    //把50000 转化为大端
    ser.sin_port  = htons(50000);
    ser.sin_addr.s_addr =  inet_addr("127.0.0.1");

    int ret = connect(sockfd,(SA)&ser,sizeof(ser));
    if(-1 == ret)
    {
    
        perror("connect");
        return 1;
    }
    int i = 10;
    while(i--)
    {

        char buf[1024]="this is tcp test";
        send(sockfd,buf,strlen(buf)+1,0);
        int rd_ret = recv(sockfd,buf,sizeof(buf),0);
        if(rd_ret<=0)
        {
            break;
        }
        printf("%s",buf);
        fflush(stdout);
        sleep(1);
    }

    close(sockfd);
    return 0;
}
