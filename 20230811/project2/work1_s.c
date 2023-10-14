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
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct sockaddr * (SA);
int main(int argc, char *argv[])
{
    int sockfd = socket(AF_INET,SOCK_DGRAM,0);
	int p=open(argv[1],O_RDONLY);
	//FILE *p1=fopen(argv[1],"r");
    if(-1 == sockfd)
    {
        perror("socket");
        exit(1);
    }
	if(-1==p)
	{
		perror("open");
		exit(1);
	}
    // man 7 ip
    struct sockaddr_in ser,cli;
    bzero(&ser,sizeof(ser));
    bzero(&cli,sizeof(cli));
    ser.sin_family = AF_INET;
    //把50000 转化为大端
    ser.sin_port  = htons(50011);
    ser.sin_addr.s_addr =  inet_addr("192.168.0.31");
    int ret = bind(sockfd,(SA)&ser,sizeof(ser));
    if(-1 == ret)
    {
        perror("bind");
        exit(1);
    }
	//fseek(p1,0,SEEK_END);
    //int i =ftell(p1);
	char buf1[512]={0};
	socklen_t len = sizeof(cli);
	recvfrom(sockfd,buf1,sizeof(buf1),0,(SA)&cli,&len);
	while(1)
	{
		char buf[1024]={0};
	//rewind(p1);
	//char *c=(char *)malloc(i);
	//fread(c,1,i,p1);
	//int i;
	//int *pi=&i;
		int ret=read(p,buf,sizeof(buf));
	//printf("%ld\n",i);
    //sendto(sockfd,pi,sizeof(i),0,(SA)&cli,sizeof(cli));
	//printf("%ld\n",i);
		if(0>=ret)
		{
			break;
		}
		socklen_t len = sizeof(cli);
		sendto(sockfd,buf,ret,0,(SA)&cli,sizeof(cli));
		recvfrom(sockfd,buf,sizeof(buf),0,(SA)&cli,&len);
	}	
	char buf[]="ok";
	sendto(sockfd,buf,strlen(buf),0,(SA)&cli,sizeof(cli));

	printf("finish\n");
	close(p);
    close(sockfd);
    return 0;
}
