#ifndef KLINK_H
#define KLINK_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
	struct node *pnext;
	struct node *ppre;
}klink_node;

typedef struct lable{
	klink_node *phead;
	int clen;
}klink_lable;

extern klink_lable *create_klink_lable(void);
extern int insert_klink_head(klink_lable *plable, klink_node *pnode);
extern int count_klink_node(klink_lable *plable, char *p,int (*check_callback)(klink_node *pnode, char *p));
extern void show_klink_node(klink_lable *plable, int flag, void (*show_callback)(klink_node *pnode));
#endif
