#ifndef STACK_H
#define STACK_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef int DateType;

typedef struct node{
	DateType date;
	struct node *pNext;
}StackNode;

typedef struct lable{
	StackNode *pHead;
	int clen;
}StackLable;

extern StackLable *CreateStack(void);
extern bool IsEmptyStack(StackLable *pLable);
extern int PushStack(StackLable *pLable, DateType date);
extern int PopStack(StackLable *pLable, DateType *pdate);
extern int GetStackTopValue(StackLable *pLable, DateType *pdate);
extern void DestoryStack(StackLable **ppLable);
extern void ShowStack(StackLable *pLable);
#endif
