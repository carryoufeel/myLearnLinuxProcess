#include "stack.h"

int main(int argc, const char *argv[])
{
	StackLable *pLable = CreateStack();
	if (NULL == pLable)
	{
		printf("fail to CreateStack");
		return -1;
	}
	PushStack(pLable, 1);
	PushStack(pLable, 2);
	PushStack(pLable, 3);
	PushStack(pLable, 4);
	PushStack(pLable, 5);
	PushStack(pLable, 6);
	PushStack(pLable, 7);
	PushStack(pLable, 8);
	PushStack(pLable, 9);
	ShowStack(pLable);
	DateType a;
	PopStack(pLable, &a);
	printf("[pop]: %d\n", a);
	
	GetStackTopValue(pLable, &a);
	printf("[Get Top]: %d\n", a);
	DestoryStack(&pLable);
	return 0;
}
