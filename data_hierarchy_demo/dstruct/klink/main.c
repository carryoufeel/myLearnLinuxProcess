#include "klink.h"
#include "flight.h"

void show_pass_callback(klink_node *pnode)
{
	if (NULL == pnode)
	{
		return;
	}
	pass_info *pass = (pass_info *)pnode;
	printf("姓名：%s  航班号：%d 座位号：%d 健康码：%s\n",
			pass->name,
			pass->flight_id,
			pass->sit_id,
			pass->heacard);
	return;
}

int check_red_callback(klink_node *pnode, char *p)
{
	if (NULL == pnode)
	{
		return 0;
	}
	pass_info *pass = (pass_info *)pnode;
	if (0 == strcmp(pass->heacard, p))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int main(int argc, const char *argv[])
{
	klink_lable *p_pass = create_klink_lable();
	if (NULL == p_pass)
	{
		printf("fail to create_klink_lable!");
		return -1;
	}
	insert_klink_head(p_pass,(klink_node *)creat_pass_date("xjzhao", 2023, 1, "g"));
	insert_klink_head(p_pass,(klink_node *)creat_pass_date("zhangsan", 2019, 2, "y"));
	insert_klink_head(p_pass,(klink_node *)creat_pass_date("lisi", 2023, 2, "r"));
	insert_klink_head(p_pass,(klink_node *)creat_pass_date("wanger", 2021, 1, "r"));
	insert_klink_head(p_pass,(klink_node *)creat_pass_date("dingzheng", 2023, 10, "g"));

	show_klink_node(p_pass, 0, show_pass_callback);
	show_klink_node(p_pass, 1, show_pass_callback);
	
	int num = count_klink_node(p_pass, "y", check_red_callback);
	printf("red num = %d\n", num);
	return 0;
}
