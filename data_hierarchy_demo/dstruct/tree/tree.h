#ifndef TREE_H
#define TREE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char TreeDateType;

typedef struct Tnode{
	TreeDateType date;
	struct Tnode *pl;
	struct Tnode *pr;
}TreeNode;

extern TreeNode *CreateBinTree(void);
extern void PreBinTreeOrder(TreeNode *pRoot);
extern void MidBinTreeOrder(TreeNode *pRoot);
extern void AftBinTreeOrder(TreeNode *pRoot);
extern void LayerBinTreeOrder(TreeNode *pRoot);
extern int GetBinTreeNodeNum(TreeNode *pRoot);
extern int GetBinTreeLayerNum(TreeNode *pRoot);
extern void DestoryBinTree(TreeNode **ppRoot);
#endif
