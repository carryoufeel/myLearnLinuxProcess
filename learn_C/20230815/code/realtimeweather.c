#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include"realtimeweather.h"
int realtimeweather(void)
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
    p= strstr(buf,"realTime");
	//p[1]=strstr(p[0],"today");
	//printf("%s",buf);
	strtok(p,"}");
	args[0]= strstr(buf,"week");
    args[1]=strstr(args[0],"wtNm");
    args[2]=strstr(args[1],"wtTemp");
	args[0] +=7;
    strtok(args[0],"\"");
	args[1]+=7;
    strtok(args[1],"\"");
	args[2]+=9;
    strtok(args[2],"\"");
	printf("星期：%s,天气：%s，当前温度：%s℃\n",args[0],args[1],args[2]);
	//strtok(p[1],"futureDay");
    //puts(p[1]);
    close(fd);
    return 0;
}
