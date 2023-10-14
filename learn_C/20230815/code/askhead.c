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
#include"askhead.h"
typedef struct sockaddr * (SA);
int askhead()
{
    //监听套接子
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
	int ret=open("deta.txt",O_CREAT|O_WRONLY|O_TRUNC,0666);
    if(-1 == sockfd)
    {
        perror("socket");
        return 1;
    }
	if(-1==ret)
	{
		perror("open");
		return 1;
	}
    // man 7 ip
    struct sockaddr_in ser;
    bzero(&ser,sizeof(ser));
    ser.sin_family = AF_INET;
    //把50000 转化为大端
    ser.sin_port  = htons(80);
    ser.sin_addr.s_addr =  inet_addr("103.205.5.249");

    int ret1 = connect(sockfd,(SA)&ser,sizeof(ser));
    if(-1 == ret1)
    {

        perror("connect");
        return 1;
    }
	//char cityNm[128]="北京";
	char area[128]="乌鲁木齐";
	scanf("%s",area);
    char * http_cmd[7]={NULL};
	http_cmd[0]=(char*)malloc(1024);
	sprintf(http_cmd[0],"GET /?app=weather.realtime&cityNm=%s&ag=today,futureDay,lifeIndex,futureHour&appkey=69832&sign=a99d50a35007641b8e3fe21ea0c6acb3&format=json HTTP/1.1\r\n",area);
    http_cmd[1]="Host: api.k780.com\r\n";
    http_cmd[2]="User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:109.0) Gecko/20100101 Firefox/116.0\r\n";
    http_cmd[3]="Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8\r\n";
    http_cmd[4]="Accept-Language: zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2\r\n";
    http_cmd[5]="Accept-Encoding: gzip, deflate\r\n";
    http_cmd[6]="Connection: keep-alive\r\n\r\n";
	//scanf("%s",cityNm);
	//printf("%s",cityNm);
	//strpl(http_cmd[0],"whatis",cityNm);
    int i = 0 ;
    for(i = 0 ;i<7;i++)
    {
        send(sockfd,http_cmd[i],strlen(http_cmd[i]),0);

    }
    char buf[1024*10]={0};
    recv(sockfd,buf,sizeof(buf),0);
	write(ret,buf,strlen(buf));
    //printf("%s\n",buf);
    fflush(stdout);
    close(sockfd);
	close(ret);
    return 0;
}
