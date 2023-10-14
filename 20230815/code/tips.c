#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include"tips.h"
int tips(void)
{
    int fd = open("./deta.txt",O_RDONLY);
    if(-1 == fd)
    {
        perror("open");
        return 1;
    }
    char buf[10*1024]={0};
	char *p=NULL;
    read(fd,buf,sizeof(buf));
    char *args[3]={NULL};
	p=strstr(buf,"uv");
	args[0]= strstr(p,"liNm");
    args[1]=strstr(args[0],"liAttr");
    args[2]=strstr(args[1],"liDese");
	args[0] +=7;
    strtok(args[0],"\"");
	args[1]+=9;
    strtok(args[1],"\"");
	args[2]+=9;
    strtok(args[2],"\"");
	printf("%s，%s，%s\n",args[0],args[1],args[2]);
    close(fd);
    int fd2 = open("./deta.txt",O_RDONLY);
    if(-1 == fd2)
    {
        perror("open");
        return 1;
    }
    char buf1[10*1024]={0};
	char *p1=NULL;
    read(fd2,buf1,sizeof(buf1));
    char *args1[3]={NULL};
	p1=strstr(buf1,"ct\"");
	args1[0]= strstr(p1,"liNm");
    args1[1]=strstr(args1[0],"liAttr");
    args1[2]=strstr(args1[1],"liDese");
	args1[0] +=7;
    strtok(args1[0],"\"");
	args1[1]+=9;
    strtok(args1[1],"\"");
	args1[2]+=9;
    strtok(args1[2],"\"");
	printf("%s，%s，%s\n",args1[0],args1[1],args1[2]);
    close(fd2);
    int fd3 = open("./deta.txt",O_RDONLY);
    if(-1 == fd3)
    {
        perror("open");
        return 1;
    }
    char buf2[10*1024]={0};
	char *p2=NULL;
    read(fd3,buf2,sizeof(buf2));
    char *args2[3]={NULL};
	p2=strstr(buf2,"xc");
	args2[0]= strstr(p2,"liNm");
    args2[1]=strstr(args2[0],"liAttr");
    args2[2]=strstr(args2[1],"liDese");
	args2[0] +=7;
    strtok(args2[0],"\"");
	args2[1]+=9;
    strtok(args2[1],"\"");
	args2[2]+=9;
    strtok(args2[2],"\"");
	printf("%s，%s，%s\n",args2[0],args2[1],args2[2]);
    close(fd3);
	return 0;
}
