#include "klink.h"

klink_lable *create_klink_lable(void)
{
	klink_lable *plable = malloc(sizeof(klink_lable));
	if (NULL == plable)
	{
		perror("fail to malloc!");
		return NULL;
	}
	plable->phead = NULL;
	plable->clen = 0;
	return plable;
}

int insert_klink_head(klink_lable *plable, klink_node *pnode)
{
	if (NULL == plable || NULL == pnode)
	{
		printf("plable or pnode is null!\n");
		return -1;
	}
	pnode->pnext = plable->phead;
	if (plable->phead != NULL)
	{
		plable->phead->ppre = pnode;
	}
	plable->phead = pnode;
	return ++(plable->clen);
}

int count_klink_node(klink_lable *plable, char *p, int (*check_callback)(klink_node *pnode, char *p))
{
	if (NULL == plable)
	{
		printf("plable is null!\n");
		return -1;
	}
	if (NULL == plable->phead)
	{
		return 0;
	}
	int count = 0;
	klink_node *pfind = plable->phead;
	while(pfind != NULL)
	{
		count += check_callback(pfind, p);
		pfind = pfind->pnext;
	}
	return count;
}

void show_klink_node(klink_lable *plable, int flag, void (*show_callback)(klink_node *pnode))
{
	if (NULL == plable)
	{
		printf("plable is null!\n");
		return;
	}
	if (NULL == plable->phead)
	{
		return;
	}

	klink_node *pfind = plable->phead;
	if (0 == flag)
	{
		while(pfind != NULL)
		{
			show_callback(pfind);
			pfind = pfind->pnext;
		}
	}
	else
	{
		while(pfind->pnext != NULL)
		{
			pfind = pfind->pnext;
		}
		while(pfind != NULL)
		{

			show_callback(pfind);
			pfind = pfind->ppre;
		}
	}
	return;
}
