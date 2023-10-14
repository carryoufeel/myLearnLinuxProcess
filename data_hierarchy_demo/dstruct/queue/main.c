#include "queue.h"

int main(int argc, const char *argv[])
{
	QueueLable *pLable = CreateQueue();
	if (NULL == pLable)
	{
		printf("fail to CreateQueue\n");
		return-1;
	}
	if (1 == IsEmptyQueue(pLable))
	{
		printf("Queue is null\n");
	}
	else
	{
		printf("Queue not null\n");
	}
	InputQueue(pLable, 1);
	InputQueue(pLable, 2);
	InputQueue(pLable, 3);
	InputQueue(pLable, 4);
	InputQueue(pLable, 5);
	InputQueue(pLable, 6);
	InputQueue(pLable, 7);
	InputQueue(pLable, 8);
	InputQueue(pLable, 9);
	ShowQueue(pLable);
	if (1 == IsFullQueue(pLable))
	{
		printf("Queue is full\n");
	}
	else
	{
		printf("Queue not full\n");
	}
	InputQueue(pLable, 10);
	
	DateType a;
	OutputQueue(pLable, &a);
 	int len = GetQueueLen(pLable);
	printf("a = %d len = %d\n", a, len);

	ShowQueue(pLable);
	ClearQueue(pLable);
	ShowQueue(pLable);
	DestoryQueue(&pLable);
	return 0;
}
