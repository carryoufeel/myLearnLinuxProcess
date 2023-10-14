#include "lqueue.h"

LqueueLable *CreateLqueueLable(void)
{
	LqueueLable *pLable = malloc(sizeof(LqueueLable));
	if (NULL == pLable)
	{
		perror("pLable is null");
		return NULL;
	}
	pLable->pHead = NULL;
	pLable->pTail = NULL;
	pLable->clen = 0;
	return pLable;
}

int IsEmptyLqueue(LqueueLable *pLable)
{
	if (NULL == pLable)
	{
		printf("pLable is null\n");
		return -1;
	}
	
	if (pLable->pHead != NULL)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int InputputLqueue(LqueueLable *pLable, DateType date)
{
	if (NULL == pLable)
	{
		printf("pLable is null\n");
		return -1;
	}
	LqueueNode *pNode = malloc(sizeof(LqueueNode));
	if (NULL == pNode)
	{
		perror("fail to malloc");
		return -2;
	}
	memcpy(&(pNode->date), &date, sizeof(DateType));
	pNode->pNext = NULL;

	if (1 == IsEmptyLqueue(pLable))
	{
		pLable->pHead = pNode;
	}
	else
	{
		pLable->pTail->pNext = pNode;
	}
	pLable->pTail = pNode;
	return ++(pLable->clen);
}

int OutputLqueue(LqueueLable *pLable, DateType *pdate)
{
	if (NULL == pLable)
	{
		printf("pLable is null\n");
		return -1;
	}

	if (1 == IsEmptyLqueue(pLable))
	{
		printf("queue is null\n");
		return -2;
	}

	LqueueNode *pNode = pLable->pHead;
	pLable->pHead = pNode->pNext;
	if (NULL == pNode->pNext)
	{
		pLable->pTail = pNode->pNext;
	}

	if (pdate != NULL)
	{
		memcpy(pdate, &(pNode->date), sizeof(DateType));
	}
	free(pNode);
	return --(pLable->clen);
}

int ClearLqueue(LqueueLable *pLable)
{
	if (NULL == pLable)
	{
		printf("pLable is null\n");
		return -1;
	}
	while(0 == IsEmptyLqueue(pLable))
	{
		OutputLqueue(pLable, NULL);
	}
	return 0;
}

void DestoryLqueue(LqueueLable **ppLable)
{
	if (NULL == ppLable || NULL == *ppLable)
	{
		printf("ppLable or *ppLable is null\n");
		return;
	}
	ClearLqueue(*ppLable);
	free(*ppLable);
	*ppLable = NULL;
	return;
}

void ShowLqueue(LqueueLable *pLable)
{
	if (NULL == pLable)
	{
		printf("pLable is null\n");
		return;
	}
	LqueueNode *pFind = pLable->pHead;
	while(pFind != NULL)
	{
		printf("%d ", pFind->date);
		pFind = pFind->pNext;
	}
	printf("\n");
	return;
}
