#include "link.h"

LinkLable *CreateLinkLable(void)
{
	LinkLable *pLable = malloc(sizeof(LinkLable));
	if (NULL == pLable)
	{
		perror("fail to malloc!");
		return NULL;
	}

	pLable->pHead = NULL;
	pLable->clen = 0;
	return pLable;
}

int InsertLinkNodeHead(LinkLable *pLable, DateType date)
{
	if (NULL == pLable)
	{
		printf("pLable is null!\n");
		return -1;
	}

	LinkNode *pNode = malloc(sizeof(LinkNode));
	if (NULL == pNode)
	{
		perror("fail to malloc!");
		return -2;
	}

	memcpy(&(pNode->date), &date, sizeof(DateType));
	pNode->pNext = NULL;

	pNode->pNext = pLable->pHead;
	pLable->pHead = pNode;
	return ++(pLable->clen);
}

int InsertLinkNodeTail(LinkLable *pLable, DateType date)
{
	if (NULL == pLable)
	{
		printf("pLable is null!\n");
		return -1;
	}

	if (NULL == pLable->pHead)
	{
		return InsertLinkNodeHead(pLable, date);
	}

	LinkNode *pNode = malloc(sizeof(LinkNode));
	if (NULL == pNode)
	{
		perror("fail to malloc!");
		return -2;
	}
	memcpy(&(pNode->date), &date, sizeof(DateType));
	pNode->pNext = NULL;

	LinkNode *pFind = pLable->pHead;
	while (pFind->pNext != NULL)
	{
		pFind = pFind->pNext;
	}
	pFind->pNext = pNode;
	return ++(pLable->clen);
}

int DeleteLinkNodeHead(LinkLable *pLable, DateType *pdate)
{
	if (NULL == pLable)
	{
		printf("pLable is null!\n");
		return -1;
	}

	if (NULL == pLable->pHead)
	{
		printf("pLable is null link!\n");
		return -2;
	}

	LinkNode *pNode = pLable->pHead;
	pLable->pHead = pNode->pNext;
	if (pdate != NULL)
	{
		memcpy(pdate, &(pNode->date), sizeof(DateType));
	}
	free(pNode);
	return --(pLable->clen);
}

int DeleteLinkNodeTail(LinkLable *pLable, DateType *pdate)
{
	if (NULL == pLable)
	{
		printf("pLable is null!\n");
		return -1;
	}

	if (NULL == pLable->pHead)
	{
		printf("pLable is null link!\n");
		return -2;
	}

	if (NULL == pLable->pHead->pNext)
	{
		return DeleteLinkNodeHead(pLable, pdate);
	}
	LinkNode *pFind = pLable->pHead;
	while(pFind->pNext->pNext != NULL)
	{
		pFind = pFind->pNext;
	}
	if (pdate != NULL)
	{
		memcpy(pdate, &(pFind->pNext->date), sizeof(DateType));
	}
	free(pFind->pNext);
	pFind ->pNext = NULL;
	return --(pLable->clen);
}

LinkNode *FindLinkNode(LinkLable *pLable, DateType date)
{
	if (NULL == pLable)
	{
		printf("pLable is null!\n");
		return NULL;
	}

	LinkNode *pNode = pLable->pHead;
	while(pNode != NULL)
	{
		if (!memcmp(&(pNode->date), &date, sizeof(DateType)))
		{
			return pNode;
		}
		pNode = pNode->pNext;
	}
}

int ModifyLinkNode(LinkLable *pLable, DateType oldDate, DateType newDate)
{
	if (NULL == pLable)
	{
		printf("pLable is null!\n");
		return -1;
	}

	LinkNode *pNode = NULL;
	do{
		pNode = FindLinkNode(pLable, oldDate);
		if (pNode != NULL)
		{
			memcpy(&(pNode->date), &newDate, sizeof(DateType));
		}
		else
		{
			break;
		}
	}while(1);
	return 0;
}

void ShowLinkNode(LinkLable *pLable)
{
	if (NULL == pLable)
	{
		printf("pLable is null!\n");
		return;
	}

	LinkNode *pNode = pLable->pHead;
	while(pNode != NULL)
	{
		printf("%d ", pNode->date);
		pNode = pNode->pNext;
	}
	printf(" clen = %d\n", pLable->clen);
	return;
}
void DestoryLinkNode(LinkLable **ppLable)
{
	if (NULL == ppLable || NULL == *ppLable)
	{
		printf("ppLable or *ppLable is null!\n");
		return;
	}
	
	while((*ppLable)->pHead != NULL)
	{
		DeleteLinkNodeHead(*ppLable, NULL);
	}
	free(*ppLable);
	*ppLable = NULL;
	return;
}
