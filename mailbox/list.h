#ifndef __LIST_H__
#define __LIST_H__
#include <pthread.h>
#include <stdlib.h>
#include <string.h>


typedef void*(*th_fun)(void* arg);
//typedef char DATATYPE[256];
typedef struct data
{
	int id;
	float temp;
	float deep;
}DATATYPE;
typedef struct mail_data
{

    pthread_t   id_of_sender;
    char       name_of_sender[256];
    pthread_t   id_of_recver;
    char       name_of_recver[256];
    DATATYPE data;
}MAIL_DATA;
typedef struct queue{
    MAIL_DATA data;
    struct queue* next;
//	int pro;
}Que, *pQue;
typedef struct thread_node
{
    pthread_t tid;         //线程id号
    char name[256];        //线程名字 ,必须唯一
    Que *mail_head, *mail_tail;
    th_fun th;
}LIST_DATA;

typedef struct Link{
    LIST_DATA elem;
    struct Link *next;
}LIST_LINK;

extern LIST_LINK * list_init();
extern LIST_LINK * list_for_each(LIST_LINK* head, char *name);

extern void list_add(LIST_LINK *head, LIST_LINK *info);
#endif
