#include "hash.h"

int main(int argc, const char *argv[])
{
	HashNode **ppTable = CreateHashTable();
	if (NULL == ppTable)
	{
		printf("fail to CreateHashTable\n");
		return -1;
	}

	int num = 0;
	while(1)
	{
		scanf("%d", &num);
		if (-1 == num)
		{
			break;
		}
		InsertHash(num);
	}
	ShowHash();
	HashNode *pNode = FindHash(5);
	if (NULL != pNode)
	{
		printf("[find] %d\n", pNode->date);
	}
	DestoryHash();
	return 0;
}
