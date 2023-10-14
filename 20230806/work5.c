#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include<time.h>
int main()
{
	struct stat buf;
	time_t tm;
	stat("./work1.c",&buf);
	if(S_ISREG(buf.st_mode))
	{
		fputc('-',stdout);
	}
	else if(S_ISDIR(buf.st_mode))
	{
		fputc('d',stdout);
	}
	else if(S_ISCHR(buf.st_mode))
	{
		fputc('c',stdout);
	}
	else if(S_ISBLK(buf.st_mode))
	{
		fputc('b',stdout);
	}
	if(S_IRUSR&&buf.st_mode)
	{
		fputc('r',stdout);
	}
	else
	{
		fputc('-',stdout);
	}
	if(S_IWUSR&&buf.st_mode)
	{
		fputc('w',stdout);
	}
	else
	{
		fputc('-',stdout);
	}
	if(S_IXUSR&&buf.st_mode)
	{
		fputc('x',stdout);
	}
	else
	{
		fputc('-',stdout);
	}
	printf("uid:%d,size:%ld,time:%s",buf.st_uid,buf.st_size,ctime(&tm));
}
