#include<stdio.h>
#include<string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int main()
{
    int i,n,j,k=0;
	int fd=open("f.txt",O_RDONLY);
    char a1[50*1024];
	read(fd,a1,sizeof(a1));
	char *p;
	p=a1;
	while( ( p=strstr(p,"ECS") ) != NULL)//p为子串与母串匹配成功
	{								  //时,子串第一个符号在母串
		k++;						  //中出现的位置地址
		p++; //p++后才能匹配下一个，否则无法退出循环
	}
}


