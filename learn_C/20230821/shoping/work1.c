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
#include <sqlite3.h>
//gcc 1.c -lsqlite3
#define BURSIZE 2048
int hex2dec(char c)
{
    if ('0' <= c && c <= '9') 
    {
        return c - '0';
    } 
    else if ('a' <= c && c <= 'f')
    {
        return c - 'a' + 10;
    } 
    else if ('A' <= c && c <= 'F')
    {
        return c - 'A' + 10;
    } 
    else 
    {
        return -1;
    }
}

char dec2hex(short int c)
{
    if (0 <= c && c <= 9) 
    {
        return c + '0';
    } 
    else if (10 <= c && c <= 15) 
    {
        return c + 'A' - 10;
    } 
    else 
    {
        return -1;
    }
}
int show(void*arg,int col,char**result,char**title)
{
	*(int*)arg =1;
	//must
	return 0;
}
//}
int show_find(void*arg,int col,char**result,char**title)
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
	sprintf(buf[0],"\n<br><a href=\"information.html=%s\"> <img src=\"%s\"></a>\n",result[0],result[1]);
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
void urldecode(char url[])
{
    int i = 0;
    int len = strlen(url);
    int res_len = 0;
    char res[BURSIZE];
    for (i = 0; i < len; ++i) 
    {
        char c = url[i];
        if (c != '%') 
        {
            res[res_len++] = c;
        }
        else 
        {
            char c1 = url[++i];
            char c0 = url[++i];
            int num = 0;
            num = hex2dec(c1) * 16 + hex2dec(c0);
            res[res_len++] = num;
        }
    }
    res[res_len] = '\0';
    strcpy(url, res);
}
int show_inf(void*arg,int col,char**result,char**title)
{
	*(int*)arg =1;    
	static int flag =  0;
	int i = 0;
	int fd = open("information.html",O_WRONLY|O_APPEND,0666);
	if(-1 == fd)
	{
		fprintf(stderr,"open error");
		return 1;
	}
	char buf[2][50*1024]={0};
	sprintf(buf[0],"\n<br><a> <img src=\"%s\"></a>\n",result[0]);
	sprintf(buf[1],"\n<h1>%s</h2>\n",result[1]);
	for (i = 0; i < col; ++i)
	{
		if (result[i] != NULL)
			write(fd,buf[i],strlen(buf[i]));
	}
	close(fd);
	//must
	return 0;
}

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
	char buf1[128]={0};
	char * http_cmd[6]={NULL};
	http_cmd[0]="HTTP/1.1 200 OK\r\n";
	http_cmd[1]="Server: mywebser\r\n";
	http_cmd[2]="Date: Mon, 14 Aug 2023 08:45:00 GMT\r\n";
	http_cmd[3]="Content-Type: text/html; charset=utf-8\r\n";
	http_cmd[4]="Connection: keep-alive\r\n";
	http_cmd[5]=buf;
	if(strlen(filename)>=5 &&0 == strncmp(&filename[strlen(filename)-3],"jpg",3))
	{
		http_cmd[3]="Content-Type:image/jpeg;charset=utf-8\r\n";
	}
	if(strlen(filename)>=4&&0==strncmp(&filename[strlen(filename)-2],"7z",2))
	{
		http_cmd[3]="Content-Type:application/octet-stream\r\n";
	}
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
	sqlite3* db=NULL;
	sqlite3* db_find=NULL;
	char* errmsg=NULL;
	int ret1 = sqlite3_open("passwd.db",&db);
	int ret2 = sqlite3_open("123.db",&db_find);
	if(SQLITE_OK != ret1||SQLITE_OK !=ret2)
	{
		fprintf(stderr,"open db, %s\n",sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;
	}
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
		printf("123:%s\n",url+1);
		if(0==strcmp(url,"/"))
		{
			send_file(conn,"./login.html");
		}
		//else if(0==strncmp(url+1,"regist", 6))
		//{
		//}
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
			char sql_cmd[1024]={0};
			sprintf(sql_cmd,"select * from user where name =\"%s\"and passwd =\"%s\";",name,pw);
			int exist_flag = 0;

			ret = sqlite3_exec(db,sql_cmd,show,&exist_flag,&errmsg);
			if(SQLITE_OK != ret)
			{
				fprintf(stderr,"exec db %s, %s\n",sql_cmd,errmsg);
				sqlite3_free(errmsg);
				sqlite3_close(db);
				return 1;
			}
			if(0 == exist_flag)
			{
				send_file(conn,"./eorro.html");
			}
			else
			{
				send_file(conn,"./find.html");
			}
		}
		else if(0==strncmp(url+1,"regist", 6))
		{
			send_file(conn,"./regist.html");
			if(strlen(url)>20)
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
				char sql_cmd[1024]={0};
				puts(name);
				puts(pw);
				sprintf(sql_cmd,"insert into user values(\"%s\",\"%s\");",name,pw);
				int exist_flag = 0;
				ret = sqlite3_exec(db,sql_cmd,show,&exist_flag,&errmsg);
				if(SQLITE_OK != ret)
				{
					fprintf(stderr,"exec db %s, %s\n",sql_cmd,errmsg);

					sqlite3_free(errmsg);
					sqlite3_close(db);
					return 1;
				}
				if(exist_flag!=0)
				{
					break;
				}
			}
			send_file(conn,"./login.html");
		}
	else if(0==strncmp(url+1,"kill", 4))
		{
			send_file(conn,"./kill.html");
			if(strlen(url)>20)
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
				char sql_cmd[1024]={0};
				puts(name);
				puts(pw);
				sprintf(sql_cmd,"delete from user where name=\"%s\";",name);
				int exist_flag = 0;
				ret = sqlite3_exec(db,sql_cmd,show,&exist_flag,&errmsg);
				if(SQLITE_OK != ret)
				{
					fprintf(stderr,"exec db %s, %s\n",sql_cmd,errmsg);

					sqlite3_free(errmsg);
					sqlite3_close(db);
					return 1;
				}
				if(exist_flag!=0)
				{
					break;
				}
			}
			send_file(conn,"./login.html");
		}

		//find?search=11111
		else if(0==strncmp(url+1,"find",4))
		{
			char *name = NULL;
			name=index(url,'=');
			name+=1;
			urldecode(name);
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
			sprintf(buf,"select goods_name,goods_img from goods where goods_name like '%%%s%%';",name);
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
			ret = sqlite3_exec(db,buf,show_find,&exist_flag,&errmsg);
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
			send_file(conn,"list.html");
		}
		else if(0==strncmp(url+1,"information",11))
		{
			char *name = NULL;
			name=index(url,'=');
			name+=1;
			urldecode(name);
			int fd=open("information.html",O_TRUNC);
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
			sprintf(buf,"select goods_desc goods_img from goods where goods_name='%s';",name);
			int exist_flag = 0;
			printf("%s",buf);
			char s1[512]="<!DOCTYPE html><html><head><meta charset=\"utf-8\"><title>列表</title></head><body>\n";
			char s2[512]="<h1>过渡消费可耻，理性消费光荣</h1>\n";
			char s3[512]="</body></html>\n";
			printf("Hello World!\n");
			int fd1=open("information.html",O_WRONLY);
			write(fd1,s1,sizeof(s1));
			write(fd1,s2,sizeof(s2));
			close(fd1);
			ret = sqlite3_exec(db,buf,show_inf,&exist_flag,&errmsg);
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
			int fd2=open("information.html",O_WRONLY|O_APPEND);
			write(fd2,s3,sizeof(s3));
			close(fd2);
			send_file(conn,"information.html");
		}

		// /1.jpg
		else if( strlen(url)>=5 &&0 == strncmp(&url[strlen(url)-3],"jpg",3))
		{
			send_file(conn,url+1);
		}
		else if(strlen(url)>=4&&0==strncmp(&url[strlen(url)-2],"7z",2))
		{
			send_file(conn,url+1);
		}
		else
		{
			send_file(conn,"./login.html");
		}
		close(conn);
	}

	close(listfd);
	return 0;
}
