#include "dlink.h"

DLinkLable *CreateDLinkLable(void)
{
	DLinkLable *pLable = malloc(sizeof(DLinkLable));
	if (NULL == pLable)
	{
		perror("fail to malloc");
		return NULL;
	}

	pLable->pHead = NULL;
	pLable->clen = 0;
	return pLable;
}

int InsertDLinkNodeHead(DLinkLable *pLable, DateType date)
{
	if (NULL == pLable)
	{
		printf("pLable is null!\n");
		return -1;
	}

	DLinkNode *pNode = malloc(sizeof(DLinkNode));
	if (NULL == pNode)
	{
		perror("fail to malloc");
		return -2;
	}
	memcpy(&(pNode->date), &date, sizeof(DateType));
	pNode->pNext = NULL;
	pNode->pPre = NULL;

	pNode->pNext = pLable->pHead;
	if (pLable->pHead != NULL)
	{
		pLable->pHead->pPre = pNode;
	}
	pLable->pHead = pNode;
	return ++(pLable->clen);
}

int InsertDLinkNodeTail(DLinkLable *pLable, DateType date)
{
	if (NULL == pLable)
	{
		printf("pLable is null!\n");
		return -1;
	}

	if (NULL == pLable->pHead)
	{
		return InsertDLinkNodeHead(pLable, date);
	}

	DLinkNode *pNode = malloc(sizeof(DLinkNode));
	if (NULL == pNode)
	{
		perror("fail to malloc");
		return -2;
	}
	memcpy(&(pNode->date), &date, sizeof(DateType));
	pNode->pNext = NULL;
	pNode->pPre = NULL;

	DLinkNode *pFind = pLable->pHead;
	while(pFind->pNext != NULL)
	{
		pFind = pFind->pNext;
	}

	pFind->pNext = pNode;
	pNode->pPre = pFind;
	return ++(pLable->clen);
}

int DeleteDLinkNodeHead(DLinkLable *pLable, DateType *pdate)
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
	
	DLinkNode *pNode = pLable->pHead;
	pLable->pHead = pNode->pNext;
	if (pLable->pHead != NULL)
	{
		pLable->pHead->pPre = NULL;
	}
	
	if (pdate != NULL)
	{
		memcpy(pdate, &(pNode->date), sizeof(DateType));
	}
	free(pNode);
	return --(pLable->clen);
}


int DeleteDLinkNodeTail(DLinkLable *pLable, DateType *pdate)
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
		return DeleteDLinkNodeHead(pLable, pdate);
	}

	DLinkNode *pFind = pLable->pHead;
	while(pFind->pNext != NULL)
	{
		pFind = pFind->pNext;
	}
	
	pFind->pPre->pNext = NULL;
	if (pdate != NULL)
	{
		memcpy(pdate, &(pFind->date), sizeof(DateType));
	}
	free(pFind);
	return --(pLable->clen);
}

DLinkNode *FindDLinkNode(DLinkLable *pLable, char *name)
{
	if (NULL == pLable)
	{
		printf("pLable is null!\n");
		return NULL;
	}
	
	if (NULL == pLable->pHead)
	{
		printf("pLable is null link!\n");
		return NULL;
	}

	DLinkNode *pFind = pLable->pHead;
	while(pFind != NULL)
	{
		if (0 == strcmp(name, pFind->date.name))
		{
			return pFind;
		}
		pFind = pFind->pNext;
	}	
	return NULL;
}

int ModifyDLinkNode(DLinkLable *pLable, char *name, int score)
{
	if (NULL == pLable)
	{
		printf("pLable is null!\n");
		return -1;
	}
	
	DLinkNode *pFind = FindDLinkNode(pLable, name);
	if (pFind != NULL)
	{
		memcpy(&(pFind->date.score), &score, sizeof(int));
	}
	else
	{
		printf("Not fond!");
		return -2;
	}
	return 0;
}
void ShowDLinkNode(DLinkLable *pLable, int flag)
{
	if (NULL == pLable)
	{
		printf("pLable is null!\n");
		return;
	}

	if (NULL == pLable->pHead)
	{
		return;
	}

	DLinkNode *pNode = pLable->pHead;
	if (0 == flag)
	{
		printf("==============正向===================\n");
		while(pNode != NULL)
		{
			printf("姓名：%s 年龄：%d 成绩：%d\n",
					pNode->date.name,
					pNode->date.age,
					pNode->date.score);
			pNode = pNode->pNext;
		}
	}
	else
	{
		printf("==============逆向===================\n");
		while(pNode->pNext != NULL)	
		{
			pNode = pNode->pNext;
		}
		while(pNode != NULL)
		{
			printf("姓名：%s 年龄：%d 成绩：%d\n",
					pNode->date.name,
					pNode->date.age,
					pNode->date.score);
			pNode = pNode->pPre;
		}
	}
	return;
}

void DestoryDLinkNode(DLinkLable **ppLable)
{
	if (NULL == ppLable || NULL == *ppLable)
	{
		printf("ppLable or *ppLable is null!");
		return;
	}
	while((*ppLable)->pHead != NULL)
	{
		DeleteDLinkNodeHead(*ppLable, NULL);
	}
	free(*ppLable);
	*ppLable = NULL;
	return;
}


