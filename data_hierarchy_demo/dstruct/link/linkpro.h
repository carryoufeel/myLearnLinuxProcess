#ifndef LINKPRO_H
#define LINKPRO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


extern LinkNode *FindLinkNodeMid(LinkLable *pLable);
extern LinkNode *FindLinkNodeTailK(LinkLable *pLable, int k);
extern int ReverseLinkNode(LinkLable *pLable);
extern int InsertSortLinkNode(LinkLable *pLable);
extern int IsLoopLinkNode(LinkLable *pLable);
extern int JosephusLoop(LinkLable *pLable);
#endif
