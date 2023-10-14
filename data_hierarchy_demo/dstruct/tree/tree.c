#include "tree.h"
#include "lqueue.h"
int Index = 0;
char preStr[] = "ABEI##J##F#K##DG##H##";
//char midStr[] = "#I#E#J#B#F#K#A#G#D#H#";

TreeNode *CreateBinTree(void)
{
	if ('#' == preStr[Index])
	{
		++Index;
		return NULL;
	}

	TreeNode *pRoot = malloc(sizeof(TreeNode));
	if (NULL == pRoot)
	{
		perror("fail to malloc");
		return NULL;
	}
	memcpy(&(pRoot->date), &preStr[Index++], sizeof(TreeDateType));
	pRoot->pl = CreateBinTree();
	pRoot->pr = CreateBinTree();
	return pRoot;
}

void PreBinTreeOrder(TreeNode *pRoot)
{
	if (NULL == pRoot)
	{
		return;
	}
	printf("%c ", pRoot->date);
	PreBinTreeOrder(pRoot->pl);
	PreBinTreeOrder(pRoot->pr);
	return;
}

void MidBinTreeOrder(TreeNode *pRoot)
{
	if (NULL == pRoot)
	{
		return;
	}
	MidBinTreeOrder(pRoot->pl);
	printf("%c ", pRoot->date);
	MidBinTreeOrder(pRoot->pr);
	return;
}

void AftBinTreeOrder(TreeNode *pRoot)
{
	if (NULL == pRoot)
	{
		return;
	}
	AftBinTreeOrder(pRoot->pl);
	AftBinTreeOrder(pRoot->pr);
	printf("%c ", pRoot->date);
	return;
}

void LayerBinTreeOrder(TreeNode *pRoot)
{
	if (NULL == pRoot)
	{
		printf("pRoot is null\n");
		return;
	}
	LqueueLable *pLable = CreateLqueueLable();
	if (NULL == pLable)
	{
		printf("fail to malloc\n");
		return;
	}
	InputputLqueue(pLable, pRoot);
	while(0 == IsEmptyLqueue(pLable))
	{
		DateType a;
		OutputLqueue(pLable, &a);
		if (a->pl != NULL)
		{
			InputputLqueue(pLable, a->pl);
		}
		if (a->pr != NULL)
		{
			InputputLqueue(pLable, a->pr);
		}
		printf("%c ", a->date);
	}
	printf("\n");
	return;
}

int GetBinTreeNodeNum(TreeNode *pRoot)
{
	if (NULL == pRoot)
	{
		return 0;
	}
	int cntl = GetBinTreeNodeNum(pRoot->pl);
	int cntr = GetBinTreeNodeNum(pRoot->pr);	
	return cntl + 1 + cntr;
}

int GetBinTreeLayerNum(TreeNode *pRoot)
{
	if (NULL == pRoot)
	{
		return 0;
	}
	
	int cntl = GetBinTreeLayerNum(pRoot->pl);
	int cntr = GetBinTreeLayerNum(pRoot->pr);
	return cntl > cntr ? (cntl + 1) : (cntr + 1);
}

void DestoryBinTree(TreeNode **ppRoot)
{
	if (NULL == ppRoot)
	{
		printf("ppRoot is null!");
		return;
	}
	if (NULL == *ppRoot)
	{
		return;
	}

	DestoryBinTree(&(*ppRoot)->pl);
	DestoryBinTree(&(*ppRoot)->pr);
	free(*ppRoot);
	*ppRoot = NULL;
	return;
}
