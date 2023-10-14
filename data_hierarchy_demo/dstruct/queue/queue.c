#include "queue.h"

QueueLable *CreateQueue(void)
{
	QueueLable *pLable = malloc(sizeof(QueueLable));
	if (NULL == pLable)
	{
		perror("fail to malloc");
		return NULL;
	}
	pLable->pBase = malloc(sizeof(DateType) * QUEUE_LENGTH);
	if (NULL == pLable->pBase)
	{
		free(pLable);
		perror("fail to malloc");
		return NULL;
	}
	pLable->head = 0;
	pLable->tail = 0;
	return pLable;
}

int IsEmptyQueue(QueueLable *pLable)
{
	if (NULL == pLable)
	{
		printf("pLable is null\n");
		return -1;
	}
	return pLable->head == pLable->tail ? 1 : 0;
}

int IsFullQueue(QueueLable *pLable)
{
	if (NULL == pLable)
	{
		printf("pLable is null\n");
		return -1;
	}
	return (pLable->head == (pLable->tail + 1) % QUEUE_LENGTH) ? 1 : 0;
}

int InputQueue(QueueLable *pLable, DateType date)
{
	if (NULL == pLable)
	{
		printf("pLable is null\n");
		return -1;
	}

	if (1 == IsFullQueue(pLable))
	{
		printf("queue is full\n");
		return -2;
	}
    memcpy(&pLable->pBase[pLable->tail], &date, sizeof(DateType));
	pLable->tail = ((pLable->tail + 1) % QUEUE_LENGTH);
	return 0;
}

int OutputQueue(QueueLable *pLable, DateType *pdate)
{
	if (NULL == pLable)
	{
		printf("pLable is null\n");
		return -1;
	}

	if (1 == IsEmptyQueue(pLable))
	{
		printf("queue is null\n");
		return -2;
	}
	if (pdate != NULL)
	{
		memcpy(pdate, &pLable->pBase[pLable->head], sizeof(DateType));
	}
	pLable->head = ((pLable->head + 1) % QUEUE_LENGTH);
	return 0;
}

int ClearQueue(QueueLable *pLable)
{
	if (NULL == pLable)
	{
		printf("pLable is null\n");
		return -1;
	}
	pLable->head = pLable->tail = 0;
	return 0;
}

int GetQueueLen(QueueLable *pLable)
{
	if (NULL == pLable)
	{
		printf("pLable is null\n");
		return -1;
	}

	int i, count = 0;
	for (i = pLable->head; i != pLable->tail; i = ((i+1) % QUEUE_LENGTH))
	{
		count++;
	}
	return count;
}

void DestoryQueue(QueueLable **ppLable)
{	
	if (NULL == ppLable || NULL == *ppLable)
	{
		printf("pLable or *ppLable is null\n");
		return;
	}
	free((*ppLable)->pBase);
	free(*ppLable);
	*ppLable = NULL;
	return;
}

void ShowQueue(QueueLable *pLable)
{
	if (NULL == pLable)
	{
		printf("pLable is null\n");
		return;
	}

	if (1 == IsEmptyQueue(pLable))
	{
		printf("queue is null\n");
		return;
	}

	int i;
	for (i = pLable->head; i != pLable->tail; i = ((i+1) % QUEUE_LENGTH))
	{
		printf("%d ", pLable->pBase[i]);	
	}
	printf("\n");
	return;
}
