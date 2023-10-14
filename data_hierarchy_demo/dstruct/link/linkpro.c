#include "link.h"
#include "linkpro.h"
LinkNode *FindLinkNodeMid(LinkLable *pLable)
{
	if (NULL == pLable)
	{
		printf("pLable is null\n");
		return NULL;
	}

	if (NULL == pLable->pHead)
	{
		printf("pLable is null lin\n");
		return NULL;
	}

	LinkNode *pFast = pLable->pHead;
	LinkNode *pSlow = pFast;
	
	while(pFast != NULL)
	{
		pFast = pFast->pNext;
		if (NULL == pFast)
		{
			break;
		}
		pFast = pFast->pNext;
		pSlow = pSlow->pNext;
	}
	return pSlow;
}

LinkNode *FindLinkNodeTailK(LinkLable *pLable, int k)
{
	if (NULL == pLable)
	{
		printf("pLable is null\n");
		return NULL;
	}
	if (NULL == pLable->pHead)
	{
		printf("pLable is null link\n");
		return NULL;
	}
	LinkNode *pPre = pLable->pHead;
	LinkNode *pAft = pPre;

	while(--k)
	{
		if (NULL == pPre->pNext)
		{
			break;
		}
		pPre = pPre->pNext;
	}

	if (k != 0)
	{
		return NULL;
	}

	while(pPre->pNext != NULL)
	{
		pPre = pPre->pNext;
		pAft = pAft->pNext;
	}
	return pAft;
}

int ReverseLinkNode(LinkLable *pLable)
{
	if (NULL == pLable)
	{
		printf("pLable is null\n");
		return -1;
	}

	if (NULL == pLable->pHead || NULL == pLable->pHead->pNext)
	{
		return 0;
	}

	LinkNode *pNode = pLable->pHead->pNext;
	LinkNode *pInsert = pNode;
	pLable->pHead->pNext = NULL;

	while(pNode != NULL)
	{
		pNode = pNode->pNext;
		pInsert->pNext = NULL;
		
		pInsert->pNext = pLable->pHead;
		pLable->pHead = pInsert;
		pInsert = pNode;
	}
	return 0;
}

int InsertSortLinkNode(LinkLable *pLable)
{
	if (NULL == pLable)
	{
		printf("pLable is null\n");
		return -1;
	}

	if (NULL == pLable->pHead || NULL == pLable->pHead->pNext)
	{
		return 0;
	}

	LinkNode *pNode = pLable->pHead->pNext;
	LinkNode *pInsert = pNode;
	pLable->pHead->pNext = NULL;

	while(pNode != NULL)
	{
		pNode = pNode->pNext;
		pInsert->pNext = NULL;

		if (memcmp(&(pLable->pHead->date), &(pInsert->date), sizeof(DateType)) >= 0)
		{
			pInsert->pNext = pLable->pHead;
			pLable->pHead = pInsert;
		}
		else
		{
			LinkNode *pFind = pLable->pHead;
			while(pFind->pNext != NULL && memcmp(&(pFind->pNext->date), &(pInsert->date), sizeof(DateType)) < 0)
			{
				pFind = pFind->pNext;
			}
			pInsert->pNext = pFind->pNext;
			pFind->pNext = pInsert;
		}
		pInsert = pNode;
	}
	return 0;
}

int IsLoopLinkNode(LinkLable *pLable)
{
	if (NULL == pLable)
	{
		printf("pLable is null\n");
		return -1;
	}

	if (NULL == pLable->pHead)
	{
		printf("pLable is null lin\n");
		return 0;
	}

	LinkNode *pFast = pLable->pHead;
	LinkNode *pSlow = pFast;
	while(pFast != NULL)
	{
		pFast = pFast->pNext;
		if (NULL == pFast)
		{
			return 0;
		}
		if (pFast == pSlow)
		{
			return 1;
		}
		pFast = pFast->pNext;
		pSlow = pSlow->pNext;	
		if (pFast == pSlow)
		{
			return 1;
		}
	}
	return 0;
}

int JosephusLoop(LinkLable *pLable)
{
	if (NULL == pLable)
	{
		printf("pLable is null\n");
		return -1;
	}
	
	LinkNode *pDel = pLable->pHead;
	LinkNode *pTemp = pDel;
	while(pLable->pHead->pNext != pLable->pHead)
	{
		pDel = pDel->pNext;
		pDel = pDel->pNext;
		pTemp = pTemp->pNext;
		pTemp->pNext = pDel->pNext;
		if (pDel == pLable->pHead)
		{
			pLable->pHead = pDel->pNext;
		}
		free(pDel);
		pDel = pTemp->pNext;
		pTemp = pDel;
	}
	return 0;
}

