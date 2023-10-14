#include <stdio.h>
#include <sqlite3.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
//gcc 1.c -lsqlite3
int show(void*arg,int col,char**result,char**title)
{
	*(int*)arg =1;    
	static int flag =  0;
	int i = 0;
	int fd = open("list.html",O_WRONLY|O_APPEND,0666);
	if(-1 == fd)
	{
		fprintf(stderr,"open error");
		return 1;
	}
	char buf[2][1024]={0};
	sprintf(buf[0],"\n<br><a> <img src=\"%s\"></a>\n",result[1]);
	sprintf(buf[1],"\n<h1>%s</h2>\n",result[0]);
	for (i = 0; i < col; ++i)
	{
		if (result[i] != NULL)
			write(fd,buf[i],strlen(buf[i]));
	}
	close(fd);
	//must
	return 0;
}
int main()
{
	int fd=open("list.html",O_TRUNC);
	close(fd);
	sqlite3* db=NULL;
	char* errmsg=NULL;
	int ret = sqlite3_open("./123.db",&db);
	if(SQLITE_OK != ret)
	{
		fprintf(stderr,"open db, %s\n",sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;
	}

	char buf[128]={0};
	sprintf(buf,"select goods_name,goods_img from goods where goods_name like '%%%s%%';","诺");
	int exist_flag = 0;
	printf("%s",buf);
	char s1[512]="<!DOCTYPE html><html><head><meta charset=\"utf-8\"><title>列表</title></head><body>\n";
	char s2[512]="<h1>过渡消费可耻，理性消费光荣</h1>\n";
	char s3[512]="</body></html>\n";
	printf("Hello World!\n");
	int fd1=open("list.html",O_WRONLY);
	write(fd1,s1,sizeof(s1));
	write(fd1,s2,sizeof(s2));
	close(fd1);
	ret = sqlite3_exec(db,buf,show,&exist_flag,&errmsg);
	if(SQLITE_OK != ret)
	{
		fprintf(stderr,"exec db %s, %s\n",buf,errmsg);
		sqlite3_free(errmsg);
		sqlite3_close(db);
		return 1;
	}
	sqlite3_close(db);
	if(0 ==exist_flag )
	{
		printf("username pass error\n");
	}
	else
	{
		printf("username pass correct\n");
	}
	int fd2=open("list.html",O_WRONLY|O_APPEND);
	write(fd2,s3,sizeof(s3));
	close(fd2);
	return 0;
}


