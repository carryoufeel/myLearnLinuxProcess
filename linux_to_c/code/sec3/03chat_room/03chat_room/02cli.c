

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
#include <fcntl.h>
#include <pthread.h>
struct sockaddr_in ser;
typedef struct sockaddr * (SA);
typedef struct
{
    char name[50];
    char buf[256];
    int type;

}MSG;
char name[50]={0};
typedef struct 
{
    MSG *msg;
    int sockfd;
}TH_ARG;
void* th1(void* arg)
{
    TH_ARG* tmp = (TH_ARG*)arg;
    while(1)
    {
        printf("to all\n");
        fgets(tmp->msg->buf,sizeof(tmp->msg->buf),stdin);//#quit
        if(0 == strcmp(tmp->msg->buf,"#quit\n"))
        {
            tmp->msg->type  =3;
        }
        else
        {
            tmp->msg->type  = 2;
        }
        strcpy(tmp->msg->name,name);

        sendto(tmp->sockfd,tmp->msg,sizeof(MSG),0,(SA)&ser,sizeof(ser));

        if(3 ==tmp->msg->type )
        {
            exit(0);
        }

    }
    

}
void* th2(void* arg)
{
    TH_ARG* tmp = (TH_ARG*)arg;
    while(1)
    {
        recvfrom(tmp->sockfd,tmp->msg,sizeof(MSG),0,NULL,NULL);
        printf("%s:%s",tmp->msg->name,tmp->msg->buf);
        fflush(stdout);
    }


}
int main(int argc, char *argv[])
{
    int sockfd = socket(AF_INET,SOCK_DGRAM,0);
    if(-1 == sockfd)
    {
        perror("socket");
        exit(1);
    }
    // man 7 ip
    bzero(&ser,sizeof(ser));
    ser.sin_family = AF_INET;
    //把50000 转化为大端
    ser.sin_port  = htons(50000);
    ser.sin_addr.s_addr =  0;
    
    MSG msg;
    bzero(&msg,sizeof(msg));

    msg.type  = 1;
    printf("input nick name");
    //strcpy(msg.name,"zhangsan");
    fgets(msg.name,sizeof(msg.name),stdin);
    msg.name[strlen(msg.name)-1]='\0';
    strcpy(name,msg.name);
    
    sendto(sockfd,&msg,sizeof(msg),0,(SA)&ser,sizeof(ser));
    TH_ARG  arg;
    arg.msg  = &msg;
    arg.sockfd = sockfd;

    pthread_t tid1,tid2;
    pthread_create(&tid1,NULL,th1,&arg);
    pthread_create(&tid2,NULL,th2,&arg);
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);

    return 0;
}

