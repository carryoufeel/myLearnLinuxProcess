/**********************************************
 * 
 * 日志记录功能文件
 * Log.c 
 *
 *********************************************/

#include <stdio.h>
#include <time.h>
#include <stdarg.h>
#include <pthread.h>
#include "Log.h"

FILE *flog = NULL;
pthread_mutex_t lock;

/* 初始化日志 */
int LogInit(void)
{
	char filename[1024] = {0};
	time_t t;
	struct tm *ptm = NULL;
	
	pthread_mutex_init(&lock, NULL);

	t = time(NULL);
	ptm = localtime(&t);
	
	sprintf(filename, "%s/debug_%04d%02d%02d.log", LOG_FILEPATH, ptm->tm_year+1900,
			                                       ptm->tm_mon+1, ptm->tm_mday);

	flog = fopen(filename, "a");
	if (NULL == flog)
	{
		printf("日志文件打开失败!\n");
		return -1;
	}
	
	return 0;
}

/* 日志记录 */
int LogWrite(char *pstr, ...)
{	
	va_list ap;
	time_t t;
	struct tm *ptm = NULL;

	t = time(NULL);
	ptm = localtime(&t);
	
	pthread_mutex_lock(&lock);
	fprintf(flog, "[%04d-%02d-%02d %02d:%02d:%02d]", ptm->tm_year+1900, ptm->tm_mon+1,
			                                         ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
	va_start(ap, pstr);
	vfprintf(flog, pstr, ap);
	va_end(ap);
	
	fflush(flog);
	pthread_mutex_unlock(&lock);

	return 0;
}

/* 日志关闭 */
int LogDeInit(void)
{
	if (flog != NULL)
	{
		fclose(flog);
		flog = NULL;
	}

	pthread_mutex_destroy(&lock);

	return 0;
}
