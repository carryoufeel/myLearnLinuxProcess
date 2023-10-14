
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
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
typedef struct sockaddr * (SA);
int send_head(int conn,char* filename)
{
    struct stat st;
    int ret = stat(filename,&st);
    if(-1 == ret)
    {
        perror("stat");
        return 1;
    }
    char buf[128]={0};
    char * http_cmd[6]={NULL};
    http_cmd[0]="HTTP/1.1 200 OK\r\n";
    http_cmd[1]="Server: mywebser\r\n";
    http_cmd[2]="Date: Mon, 14 Aug 2023 08:45:00 GMT\r\n";
    http_cmd[3]="Content-Type: text/html; charset=utf-8\r\n";
    http_cmd[4]="Connection: keep-alive\r\n";
    http_cmd[5]=buf;
    sprintf(buf, "content-length: %ld\r\n\r\n",st.st_size);
    int i = 0;
    for(i = 0 ;i<6;i++)
    {
        send(conn,http_cmd[i],strlen(http_cmd[i]),0);
    }
    
    return 0;
}
int send_file(int conn,char* filename)
{
    send_head(conn,filename);
    int fd =  open(filename,O_RDONLY);
    if(-1== fd)
    {
        perror("open");
        return 1;
    }

    while(1)
    {
        char buf[1024]={0};
        int rd_ret = read(fd,buf,sizeof(buf));
        if(rd_ret<=0)
        {
            break;
        }
        send(conn,buf,rd_ret,0);
    }
    close(fd);
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
    ser.sin_port  = htons(80);
    ser.sin_addr.s_addr =  INADDR_ANY;

    int ret = bind(listfd,(SA)&ser,sizeof(ser));
    if(-1 == ret)
    {
        perror("bind");
        return 1;
    }
    listen(listfd,3);
    socklen_t len = sizeof(cli);
    while(1)
    {
        char buf[1024]={0};
        int conn =accept(listfd,(SA)&cli,&len);
        if(-1 == conn)
        {
            perror("accept");
            continue;
        }

        int rd_ret = recv(conn,buf,sizeof(buf),0);
        if(rd_ret<=0)
        {
            continue;
        }
        printf("%s\n",buf);
        // GET / HTTP/1.1 
        //
        char* methord =NULL;
        char * url =NULL;
        char * ver=NULL;
        methord = strtok(buf," ");
        url = strtok(NULL," ");
        ver= strtok(NULL,"\r");
        if(0==strcmp(url,"/"))
        {
            send_file(conn,"./3.html");
        }
        // /login?username=zhangsan&userpw=123
        else if(0 == strncmp(url+1,"login",5))
        {
            char *name = NULL;
            char* pw = NULL;
            char* end =NULL;
            name=index(url,'=');
            name+=1;
            end = index(name,'&');
            *end ='\0';

            pw = index(end+1,'=');
            pw+=1;

            if(0 == strcmp(name,"zhangsan") && 0 == strcmp(pw,"123"))
            {
                send_file(conn,"./1.html");
            }
            else
            {
                send_file(conn,"./4.html");
            }
        }
        // /1.jpg
        else if( strlen(url)>=5 &&0 == strncmp(&url[strlen(url)-3],"jpg",3))
        {
            send_file(conn,url+1);
        }
        close(conn);
    }

    close(listfd);
    return 0;
}
