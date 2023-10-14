#ifndef LINK_H
#define LINK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int DateType;
typedef struct node{
	DateType date;
	struct node *pNext;
}LinkNode;

typedef struct lable{
	LinkNode *pHead;
	int clen;
}LinkLable;

extern LinkLable *CreateLinkLable(void);
extern int InsertLinkNodeHead(LinkLable *pLable, DateType date);
extern void ShowLinkNode(LinkLable *pLable);
extern int InsertLinkNodeTail(LinkLable *pLable, DateType date);
extern int DeleteLinkNodeHead(LinkLable *pLable, DateType *pdate);
extern LinkNode *FindLinkNode(LinkLable *pLable, DateType date);
extern int ModifyLinkNode(LinkLable *pLable, DateType oldDate, DateType newDate);
extern int DeleteLinkNodeTail(LinkLable *pLable, DateType *pdate);
extern void DestoryLinkNode(LinkLable **ppLable);
#endif
