#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include  <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#define MAXUSER 10
typedef struct sockaddr* (SA);
typedef struct
{
    char name[50];
    char buf[256];
    int type;

}MSG;
typedef struct
{

    struct sockaddr_in cli;
    int flag;
}LIST;
LIST list[MAXUSER];
void do_login(int sockfd,struct sockaddr_in* cli,MSG*msg)// 1 name buf
{
    int i = 0 ;
    strcpy(msg->buf,"online");
    for(i = 0 ;i<MAXUSER;i++)
    {

        if(1 == list[i].flag)
        {
            sendto(sockfd,msg,sizeof(MSG),0,(SA)&list[i].cli,sizeof(list[i].cli));
        }
    }


    for(i = 0 ;i<MAXUSER;i++)
    {

        if(0 == list[i].flag)
        {
            //sendto(sockfd,msg,sizeof(MSG),0,list[i].cli,sizeof(list[i].cli));
            //list[i].cli = *cli;
            memcpy(&list[i].cli,cli,sizeof(struct sockaddr_in));
            list[i].flag = 1;
            break;
        }
    }

}

void do_chat(int sockfd,struct sockaddr_in* cli,MSG*msg)
{
    int i=  0;
    for(i = 0 ;i<MAXUSER;i++)
    {

        if(1 == list[i].flag && 0 != memcmp(&list[i].cli , cli,sizeof(struct sockaddr_in)))
        {
            sendto(sockfd,msg,sizeof(MSG),0,(SA)&list[i].cli,sizeof(list[i].cli));


        }
    }
}

void do_quit(int sockfd,struct sockaddr_in* cli,MSG*msg)
{

    int i = 0 ;
    strcpy(msg->buf,"offline");
    for(i = 0 ;i<MAXUSER;i++)
    {

        if(1 == list[i].flag && 0 != memcmp(&list[i].cli,cli,sizeof(struct sockaddr_in)))
        {
            sendto(sockfd,msg,sizeof(MSG),0,(SA)&list[i].cli,sizeof(list[i].cli));
        }
        else if( 0 == memcmp(&list[i].cli,cli,sizeof(struct sockaddr_in)))
        {

            list[i].flag =  0;
        }
    }



}
int main()
{
    int sockfd = socket(AF_INET,SOCK_DGRAM,0);
    if(-1 == sockfd)
    {
        perror("socket");
        return 1;

    }
    struct sockaddr_in ser,cli;
    bzero(&ser,sizeof(ser));
    bzero(&cli,sizeof(cli));
    ser.sin_family =AF_INET;
    ser.sin_port = htons(50000);
    ser.sin_addr.s_addr = INADDR_ANY ;
    int ret = bind(sockfd,(SA)&ser,sizeof(ser));
    if(-1 == ret)
    {
        perror("bind");
        return 1;
    }
    socklen_t len = sizeof(cli);
    while(1)
    {
        MSG msg;
        recvfrom(sockfd,&msg,sizeof(msg),0,(SA)&cli,&len);
        switch (msg.type) {
        case 1:
            do_login(sockfd,&cli,&msg);
            break;
        case 2:
            do_chat(sockfd,&cli,&msg);
            break;
        case 3:
            do_quit(sockfd,&cli,&msg);
            break;
        default:
            break;
        }


    }

    printf("Hello World!\n");
    return 0;
}
