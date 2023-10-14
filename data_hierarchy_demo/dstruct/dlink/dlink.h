#ifndef DLINK_H
#define DLINK_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stu{
	char name[32];
	int age;
	int score;
}DateType;

typedef struct node{
	DateType date;
	struct node *pNext;
	struct node *pPre;
}DLinkNode;

typedef struct lable{
	DLinkNode *pHead;
	int clen;
}DLinkLable;

extern DLinkLable *CreateDLinkLable(void);
extern int InsertDLinkNodeHead(DLinkLable *pLable, DateType date);
extern void ShowDLinkNode(DLinkLable *pLable, int flag);
extern int InsertDLinkNodeTail(DLinkLable *pLable, DateType date);
extern int DeleteDLinkNodeHead(DLinkLable *pLable, DateType *pdate);
extern int DeleteDLinkNodeTail(DLinkLable *pLable, DateType *pdate);
extern void DestoryDLinkNode(DLinkLable **ppLable);
extern DLinkNode *FindDLinkNode(DLinkLable *pLable, char *name);
extern int ModifyDLinkNode(DLinkLable *pLable, char *name, int score);
#endif
