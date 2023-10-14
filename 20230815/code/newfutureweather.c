#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include<fcntl.h>
int main()
{
	int fd=open("./deta.txt",O_RDONLY);
	char *want_item[]={"dateYmd","week","wtNm1","wtNm2","wtTemp1","wtTemp2"};
	char * args[7]={0};
	int i = 0 ;
	char data[10*1024]={0};
	read(fd,data,sizeof(data));
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
		char *inner[6]={NULL};
		char* end = NULL;
		for(i =0;i<6;i++)
		{
			inner[i] = strstr(start,want_item[i]);
			inner[i]+=strlen(want_item[i])+3 ;
		}

		for(i = 0 ;i<6;i++)
		{
			end = index(inner[i],'"');
			*end = '\0';
		}
			printf("日期：%s，星期：%s，天气：%s转%s，温度：%s℃ /%s℃\n",
				   inner[0],inner[1],inner[2],inner[3],inner[4],inner[5]);
			fflush(stdout);
			close(fd);

	}
}
