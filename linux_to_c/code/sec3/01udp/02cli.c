
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
    struct sockaddr_in ser;
    bzero(&ser,sizeof(ser));
    ser.sin_family = AF_INET;
    //把50000 转化为大端
    ser.sin_port  = htons(50000);
    ser.sin_addr.s_addr =  inet_addr("192.168.92.129");
    int i =5;
    while(i--)
    {   
        char buf[512]="hello,this udp test";
        sendto(sockfd,buf,strlen(buf)+1,0,(SA)&ser,sizeof(ser));
        recvfrom(sockfd,buf,sizeof(buf),0,NULL,NULL);
        printf("%s",buf);
        fflush(stdout);
        sleep(1);
    }

    close(sockfd);
    return 0;
}
