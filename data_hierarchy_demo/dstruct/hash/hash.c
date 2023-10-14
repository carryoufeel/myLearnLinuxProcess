#include "hash.h"

HashNode *hashTable[HASH_SIZE];

HashNode *(*p)[HASH_SIZE];

HashNode **CreateHashTable(void)
{
	int len = sizeof(HashNode *) * HASH_SIZE;
	HashNode **ppTable = malloc(len);
	if (NULL == ppTable)
	{
		perror("fail to malloc");
		return NULL;
	}
	memset(ppTable, 0, len);
	return ppTable;
}



int IsEmptyHash(void)
{
	int i = 0;
	for (i = 0; i < HASH_SIZE; i++)
	{
		if (hashTable[i] != NULL)
		{
			return 0;
		}
	}
	return 1;
}

int HashFunction(DateKey key)
{
	return key % HASH_SIZE;
}

int InsertHash(DateType date)
{
	int add = HashFunction(date);

	HashNode *pNode = malloc(sizeof(HashNode));
	if (NULL == pNode)
	{
		perror("fail to malloc");
		return -1;
	}
	memcpy(&(pNode->date), &date, sizeof(DateType));
	pNode->pNext = NULL;

	pNode->pNext = hashTable[add];
	hashTable[add] = pNode;
	return 0;
}

HashNode *FindHash(DateType date)
{
	int add = HashFunction(date);

	HashNode *pFind = hashTable[add];
	while (pFind != NULL)
	{
		if (0 == memcmp(&(pFind->date), &date, sizeof(DateType)))
		{
			return pFind;
		}
		pFind = pFind->pNext;
	}
	return NULL;
}

void DestoryHash(void)
{
	int i = 0;
	for (i = 0; i < HASH_SIZE; i++)
	{
		while (hashTable[i] != NULL)
		{
			HashNode *pNode = hashTable[i];
			hashTable[i] = pNode->pNext;
			free(pNode);
		}
	}
	return;
}

void ShowHash(void)
{
	int i = 0;
	for (i = 0; i < HASH_SIZE; i++)
	{
		HashNode *pNode = hashTable[i];	
		while(pNode != NULL)
		{
			printf("%d ", pNode->date);
			pNode = pNode->pNext;
		}
		printf("\n");
	}
	return;
}

