#ifndef HASH_H
#define HASH_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HASH_SIZE (10)
typedef int DateKey;
typedef int DateType;
typedef struct node{
	DateType date;
	struct node *pNext;
}HashNode;

extern HashNode **CreateHashTable(void);
extern int IsEmptyHash(void);
extern int HashFunction(DateKey key);
extern int InsertHash(DateType date);
extern HashNode *FindHash(DateType date);
extern void DestoryHash(void);
extern void ShowHash(void);
#endif
