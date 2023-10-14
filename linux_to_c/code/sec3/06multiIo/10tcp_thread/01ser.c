
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
#include <pthread.h>
#include <semaphore.h>
sem_t sem_conn;
void* th(void* arg)
{
    pthread_detach(pthread_self());
    int conn =  *(int*)arg;
    sem_post(&sem_conn);
    while(1)
    {
        char buf[1024]={0};
        int rd_ret = recv(conn,buf,sizeof(buf),0);
        if(rd_ret<=0)
        {
            printf("cli offline\n");
            close(conn);
            break;
        }
        time_t tm;
        time(&tm);
        sprintf(buf,"%s %s",buf,ctime(&tm));
        send(conn,buf,strlen(buf)+1,0);
    }

    pthread_exit(NULL);
}
typedef struct sockaddr * (SA);
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
    char buf[1024]={0};
    sem_init(&sem_conn,0,0);
    while(1)
    {
        //通信套接子
        int conn =accept(listfd,(SA)&cli,&len);
        if(-1 == conn)
        {
            perror("accept");
            return 1;
        }
        
        pthread_t tid;
        pthread_create(&tid,NULL,th,&conn);
        sem_wait(&sem_conn);

     }
    sem_destroy(&sem_conn);
    close(listfd);
    return 0;
}
