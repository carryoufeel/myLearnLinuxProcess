#include "tree.h"

int main(int argc, const char *argv[])
{
	TreeNode *pRoot = CreateBinTree();
	if (NULL == pRoot)
	{
		printf("fail to CreateBinTree\n");
		return -1;
	}
	PreBinTreeOrder(pRoot);
	printf("\n");
	MidBinTreeOrder(pRoot);
	printf("\n");
	AftBinTreeOrder(pRoot);
	printf("\n");
	LayerBinTreeOrder(pRoot);

	int ret = GetBinTreeNodeNum(pRoot);
	printf("node num = %d\n", ret);
	ret = GetBinTreeLayerNum(pRoot);
	printf("layer num = %d\n", ret);
	
	DestoryBinTree(&pRoot);
	return 0;
}
