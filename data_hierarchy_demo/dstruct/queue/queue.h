#ifndef QUEUE_H
#define QUEUE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define QUEUE_LENGTH (10)
typedef int DateType;

typedef struct lable{
	DateType *pBase;
	int head;
	int tail;
}QueueLable;

extern QueueLable *CreateQueue(void);
extern int IsEmptyQueue(QueueLable *pLable);
extern int IsFullQueue(QueueLable *pLable);
extern int InputQueue(QueueLable *pLable, DateType date);
extern int OutputQueue(QueueLable *pLable, DateType *pdate);
extern int ClearQueue(QueueLable *pLable);
extern int GetQueueLen(QueueLable *pLable);
extern void DestoryQueue(QueueLable **ppLable);
extern void ShowQueue(QueueLable *pLable);
#endif
