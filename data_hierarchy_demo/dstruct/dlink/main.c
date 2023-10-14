#include "dlink.h"

int main(int argc, const char *argv[])
{
	DLinkLable *pLable = CreateDLinkLable();
	if (NULL == pLable)
	{
		printf("fail to CreateDLinkLable!");
		return -1;
	}
	DateType stus[5] = {
		{"zhangsan", 18, 88},
		{"madongmei", 12, 100},
		{"lisi", 28, 120},
		{"wanger", 35, 60},
		{"mazi", 10, 59}
	};
	InsertDLinkNodeHead(pLable, stus[0]);
	InsertDLinkNodeTail(pLable, stus[1]);
	InsertDLinkNodeHead(pLable, stus[2]);
	InsertDLinkNodeTail(pLable, stus[3]);
	InsertDLinkNodeHead(pLable, stus[4]);
	ShowDLinkNode(pLable, 0);
	ShowDLinkNode(pLable, 1);
	DateType stu;
	DeleteDLinkNodeHead(pLable, &stu);
	printf("delete 姓名：%s 年龄：%d 成绩：%d\n",
			stu.name,
			stu.age,
			stu.score);
	DeleteDLinkNodeTail(pLable, &stu);
	printf("delete 姓名：%s 年龄：%d 成绩：%d\n",
			stu.name,
			stu.age,
			stu.score);
	ShowDLinkNode(pLable, 0);
	ShowDLinkNode(pLable, 1);
	DLinkNode *pFind = FindDLinkNode(pLable, "mazi");
	if (pFind != NULL)
	{
		printf("pFind name = %s\n", pFind->date.name);
	}
	else
	{
		printf("Not Find\n");
	}
	ModifyDLinkNode(pLable, "zhangsan", 100);

	ShowDLinkNode(pLable, 0);
	ShowDLinkNode(pLable, 1);
	DestoryDLinkNode(&pLable);
	return 0;
}
