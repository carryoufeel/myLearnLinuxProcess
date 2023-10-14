#ifndef LQUEUE_H
#define LQUEUE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int DateType;
typedef struct node{
	DateType date;
	struct node *pNext;
}LqueueNode;
typedef struct lable{
	LqueueNode *pHead;
	LqueueNode *pTail;
	int clen;
}LqueueLable;
 
extern LqueueLable *CreateLqueueLable(void);
extern int IsEmptyLqueue(LqueueLable *pLable);
extern int InputputLqueue(LqueueLable *pLable, DateType date);
extern int OutputLqueue(LqueueLable *pLable, DateType *pdate);
extern void ShowLqueue(LqueueLable *pLable);
extern int ClearLqueue(LqueueLable *pLable);
extern void DestoryLqueue(LqueueLable **ppLable);
#endif
