#include <stdlib.h>
#include <stdio.h>
struct Node
{
	int data;
	struct Node *next;
};            //创建节点的值域和指针域

void push_front(struct Node *pHand,int n)
{
	struct Node *pNew=malloc(sizeof(struct Node));
	pNew->next=pHand->next;
	pHand->next=pNew;
	pNew->data=n;
}
//
void printlist(struct Node *pHand)
{
	struct Node *p=pHand->next;
	while(p!=NULL)
	{
		printf("%d\n",p->data);
		p=p->next;
	}
}

int isEmpty(struct Node *pHand)
{
	if(pHand->next==NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int length(struct Node *pHand)
{
	struct Node *p=pHand->next;
	int i=0;
	while(p!=NULL)
	{
		i++;
		p=p->next;
	}
	return i;
}

void push_back(struct Node *pHand,int n)
{
	if(!isEmpty(pHand))
	{
		struct Node *p=pHand->next;
		while(p->next!=NULL)
		{
			p=p->next;
		}
		struct Node *pNew=malloc(sizeof(struct Node));
		p->next=pNew;
		pNew->next=NULL;
		pNew->data=n;
	}
	else
	{
		push_front(pHand,n);
	}
}

void pop_front(struct Node *pHand)
{
	if(!isEmpty(pHand))
	{
		struct Node *p=pHand->next;
		pHand->next=p->next;
		free(p);
	}
}

void pop_back(struct Node *pHand)
{
	struct Node *p=pHand->next;
	if(length(pHand)>=2)
	{
		while(p->next->next!=NULL)
		{
			p=p->next;
		}
		free(p->next);
		p->next=NULL;
	}
	else
	{
		pop_front(pHand);
	}
}

void clear(struct Node *pHand)
{
	while(!isEmpty(pHand))
	{
		pop_front(pHand);
	}
}

int main(void)
{
	struct Node head={0,NULL};//创建首节点
	struct Node *pHand =&head;//让首节点指向头节点
	//printf("isEmpty=%d\n",isEmpty(pHand));
	//push_front(pHand,1);
	//push_front(pHand,2);
	//pop_front(pHand);
	//printf("isEmpty=%d\n",isEmpty(pHand));
	//push_front(pHand,3);
	//push_back(pHand,4);
	pop_back(pHand);
	printlist(pHand);
	//printf("%d\n",length(pHand));
	clear(pHand);
	return 0;
}
