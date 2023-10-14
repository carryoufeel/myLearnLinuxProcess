#include "stack.h"
StackLable *CreateStack(void)
{
	StackLable *pLable = malloc(sizeof(StackLable));
	if (NULL == pLable)
	{
		perror("fail to malloc!");
		return NULL;
	}
	pLable->pHead = NULL;
	pLable->clen = 0;
	return pLable;
}

bool IsEmptyStack(StackLable *pLable)
{
	if (NULL == pLable)
	{
		printf("pLable is NULL!");
		return false;
	}
	if (NULL == pLable->pHead)
	{
		return true;
	}
	return false;
}

int PushStack(StackLable *pLable, DateType date)
{
	if (NULL == pLable)
	{
		printf("pLable is NULL!");
		return -1;
	}
	
	StackNode *pNode = malloc(sizeof(StackNode));
	if (NULL == pNode)
	{
		perror("fail to malloc");
		return -2;
	}
	memcpy(&(pNode->date), &date, sizeof(DateType));
	pNode->pNext = NULL;
	
	pNode->pNext = pLable->pHead;
	pLable->pHead = pNode;
	return ++(pLable->clen);
}

int PopStack(StackLable *pLable, DateType *pdate)
{
	if (NULL == pLable)
	{
		printf("pLable is NULL!");
		return -1;
	}
	
	if (IsEmptyStack(pLable))
	{
		printf("stack is null\n");
		return -2;
	}

	StackNode *pNode = pLable->pHead;
	pLable->pHead = pNode->pNext;
	if (pdate != NULL)
	{
		memcpy(pdate, &(pNode->date), sizeof(DateType));
	}
	free(pNode);
	return --(pLable->clen);
}

int GetStackTopValue(StackLable *pLable, DateType *pdate)
{
	if (NULL == pLable)
	{
		printf("pLable is NULL!");
		return -1;
	}
	
	if (IsEmptyStack(pLable))
	{
		printf("stack is null\n");
		return -2;
	}

	StackNode *pNode = pLable->pHead;
	if (pdate != NULL)
	{
		memcpy(pdate, &(pNode->date), sizeof(DateType));
	}
	return pLable->clen;
}

void DestoryStack(StackLable **ppLable)
{
	if (NULL == ppLable || NULL == *ppLable)
	{
		printf("pLable or *ppLable is null\n");
		return;
	}

	while ((*ppLable)->pHead != NULL)
	{
		PopStack(*ppLable, NULL);
	}
	free(*ppLable);
	*ppLable = NULL;
	return;
}

void ShowStack(StackLable *pLable)
{
	if (NULL == pLable)
	{
		printf("pLable is NULL!");
		return;
	}
	
	StackNode *pNode = pLable->pHead;
	while (pNode != NULL)
	{
		printf("%d ", pNode->date);
		pNode = pNode->pNext;
	}
	printf("\n");
	return;
}
