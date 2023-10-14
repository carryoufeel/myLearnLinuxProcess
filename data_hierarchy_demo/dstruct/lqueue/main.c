#include "lqueue.h"

int main(int argc, const char *argv[])
{
	LqueueLable *pLable = CreateLqueueLable();
	if (NULL == pLable)
	{
		printf("fail to CreateLqueueLable");
		return -1;
	}
	InputputLqueue(pLable, 1);
	InputputLqueue(pLable, 2);
	InputputLqueue(pLable, 3);
	InputputLqueue(pLable, 4);
	OutputLqueue(pLable, NULL);
	InputputLqueue(pLable, 5);
	InputputLqueue(pLable, 6);
	InputputLqueue(pLable, 7);
	InputputLqueue(pLable, 8);

	ShowLqueue(pLable);
	ClearLqueue(pLable);
	ShowLqueue(pLable);
	DestoryLqueue(&pLable);
	return 0;
}
