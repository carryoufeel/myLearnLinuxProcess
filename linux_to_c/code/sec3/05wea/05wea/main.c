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
void do_furture(char * data)
{
    char *want_item[]={"days","week","citynm","temperature","weather"};
    char * args[7]={0};
    int i = 0 ;
    char * tmp = data;
    for(i = 0 ;i<7;i++)
    {

        args[i] = strstr(tmp,"days");
        if(NULL == args[i])
        {

            break;
        }
        tmp  = args[i]+1;

    }

    int j = i;
    int k  = 0;
    while(j--)
    {


        char *start = args[k++];
        char *inner[5]={NULL};
        char* end = NULL;
        for(i =0;i<5;i++)
        {
            inner[i] = strstr(start,want_item[i]);
            inner[i]+=strlen(want_item[i])+3 ;

        }

        for(i = 0 ;i<5;i++)
        {
            end = index(inner[i],'"');
            *end = '\0';
        }


        printf("%s:%s:%s:%s:%s\n",inner[0],inner[1],inner[2],inner[3],inner[4]);
        fflush(stdout);
    }

}
int main()
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
    ser.sin_port  = htons(80);
    ser.sin_addr.s_addr =  inet_addr("103.205.5.249");

    int ret = connect(sockfd,(SA)&ser,sizeof(ser));
    if(-1 == ret)
    {

        perror("connect");
        return 1;
    }

    char * http_cmd[7]={NULL};
    http_cmd[0]="GET /?app=weather.future&cityNm=西安&appkey=10003&sign=b59bc3ef6191eb9f747dd4e83c99f2a4&format=json HTTP/1.1\r\n";
    http_cmd[1]="Host: api.k780.com\r\n";
    http_cmd[2]="Connection: keep-alive\r\n";
    http_cmd[3]="User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/80.0.3987.87 Safari/537.36 SE 2.X MetaSr 1.0\r\n";
    http_cmd[4]="Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9\r\n";
    http_cmd[5]="Accept-Encoding: gzip, deflate\r\n";
    http_cmd[6]="Accept-Language: zh-CN,zh;q=0.9\r\n\r\n";

    int i = 0 ;
    for(i = 0 ;i<7;i++)
    {
        send(sockfd,http_cmd[i],strlen(http_cmd[i]),0);

    }
    char total_buf[8*1024]={0};
    while(1)
    {
        char buf[512]={0};
        recv(sockfd,buf,sizeof(buf)-1,0);
        strcat(total_buf,buf);
        if(strstr(total_buf,"\r\n0\r\n"))
        {
            break;
        }
    }


    printf("%s",total_buf);
    fflush(stdout);

    do_furture(total_buf);


    close(sockfd);
    return 0;
}
