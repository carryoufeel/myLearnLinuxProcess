#ifndef __LOG_H__
#define __LOG_H__


#define LOG_FILEPATH		"."			//日志存放路径

extern int LogInit(void);
extern int LogWrite(char *pstr, ...);
extern int LogDeInit(void);

#endif
