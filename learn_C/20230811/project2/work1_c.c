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
	int fd = socket(AF_INET,SOCK_DGRAM,0);
	//FILE *p=fopen(argv[1],"w");
	int p=open(argv[1],O_WRONLY|O_CREAT|O_TRUNC,0666);
	if(-1 == fd)
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
	struct sockaddr_in ser;
	bzero(&ser,sizeof(ser));
	ser.sin_family = AF_INET;
	//把50000 转化为大端
	ser.sin_port  = htons(50011);
	ser.sin_addr.s_addr =  inet_addr("127.0.0.1");
	char buf[512]="来份图";
	//recvfrom(fd,c,sizeof(i),0,NULL,NULL);
	//char *p1=(char*)malloc(i);
	//char p1[74305]={0};
	//printf("%ld\n",i);
	//printf("ok\n");
	sendto(fd,buf,strlen(buf),0,(SA)&ser,sizeof(ser));

	while(1)
	{
		char buf[1024]={0};
		int ret=recvfrom(fd,buf,sizeof(buf),0,NULL,NULL);
		if(strcmp("ok",buf)==0)
		{
			break;
		}
		write(p,buf,ret);
		strcpy(buf,"good");
		sendto(fd,buf,strlen(buf),0,(SA)&ser,sizeof(ser));
		if(0>=ret)
		{
			break;	
		}
	}
	printf("ok\n");
	//fwrite(p1,1,i,p);
	close(fd);
	close(p);
	return 0;
}

