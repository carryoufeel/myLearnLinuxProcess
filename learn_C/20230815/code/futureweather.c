#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include"futureweathe.h"
int futureweather()
{
	//p[1]=strstr(p[0],"today");
	//printf("%s",buf);
	for(int i=0;i<6;i++)
	{
		int fd = open("./deta.txt",O_RDONLY);
		if(-1 == fd)
		{
			perror("open");
			return 1;
		}
		char buf[10*1024]={0};
		char *p=NULL;
		lseek(fd,1000+670*i,SEEK_SET);
		read(fd,buf,sizeof(buf));
		char *args[6]={NULL};
		//p= strstr(buf,"futureDay");
		args[0]= strstr(buf,"dateYmd");
		args[1]=strstr(args[0],"week");
		args[2]=strstr(args[1],"wtNm1");
		args[3]=strstr(args[2],"wtNm2");
		args[4]=strstr(args[3],"wtTemp1");
		args[5]=strstr(args[4],"wtTemp2");
		args[0] +=10;
		strtok(args[0],"\"");
		args[1]+=7;
		strtok(args[1],"\"");
		args[2]+=8;
		strtok(args[2],"\"");
		args[3] +=8;
		strtok(args[3],"\"");
		args[4] +=10;
		strtok(args[4],"\"");
		args[5] +=10;
		strtok(args[5],"\"");

		printf("日期：%s，星期：%s，天气：%s转%s，温度：%s℃ /%s℃\n",
			   args[0],args[1],args[2],args[3],args[4],args[5]);
		close(fd);
	}
	//strtok(p[1],"futureDay");
	//puts(p[1]);
	return 0;
}
