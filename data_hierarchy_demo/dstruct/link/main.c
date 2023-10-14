#include "link.h"
#include "linkpro.h"

int main(int argc, const char *argv[])
{
 	LinkLable *pLable = CreateLinkLable();	
	if (NULL == pLable)
	{
		printf("fail to CreateLinkLable!\n");
		return -1;
	}
	//InsertLinkNodeTail(pLable, 0);
	InsertLinkNodeHead(pLable, 1);
	InsertLinkNodeTail(pLable, 2);
	InsertLinkNodeHead(pLable, 3);
	InsertLinkNodeTail(pLable, 4);
	InsertLinkNodeHead(pLable, 5);
	InsertLinkNodeTail(pLable, 6);
	InsertLinkNodeHead(pLable, 7);
	InsertLinkNodeTail(pLable, 8);
	InsertLinkNodeHead(pLable, 9);
	ShowLinkNode(pLable);
	//ReverseLinkNode(pLable);
	//ShowLinkNode(pLable);
	//InsertSortLinkNode(pLable);
	//ShowLinkNode(pLable);

	LinkNode *pFmid = FindLinkNodeMid(pLable); 
	if (pFmid != NULL)
	{
		printf("mid = %d\n", pFmid->date);
	}
	int k = 1;
	//scanf("%d", &k);
	LinkNode *pTk = FindLinkNodeTailK(pLable, k);
	if (pTk != NULL)
	{
		pTk->pNext = pLable->pHead;
	}
	
	int ret = IsLoopLinkNode(pLable);
	printf("ret = %d\n", ret);

	JosephusLoop(pLable);
	printf("Josephus = %d\n", pLable->pHead->date);
#if 0	
	ShowLinkNode(pLable);
	DateType a;
	DeleteLinkNodeHead(pLable, &a);
	printf("head a = %d\n", a);
	DeleteLinkNodeTail(pLable, &a);
	printf("tail a = %d\n", a);
	LinkNode *pNode = FindLinkNode(pLable, 6);
	if (pNode != NULL)
	{
		printf("pNode = %d\n", pNode->date);
	}
	ModifyLinkNode(pLable, 4, 11);
	ShowLinkNode(pLable);
	DestoryLinkNode(&pLable);
	ShowLinkNode(pLable);
#endif
	return 0;
}
