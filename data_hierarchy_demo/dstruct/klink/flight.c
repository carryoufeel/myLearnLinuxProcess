#include "flight.h"

pass_info *creat_pass_date(char *name, int flight_id, int sit_id, char *heacard)
{
	if (NULL == name || NULL == heacard)
	{
		printf("name or heacard is null\n");
		return NULL;
	}
	pass_info*ppass = malloc(sizeof(pass_info));
	if (NULL == ppass)
	{
		perror("fail to malloc!");
		return NULL;
	}
	ppass->node.pnext = NULL;
	ppass->node.ppre = NULL;

	strcpy(ppass->name, name);
	ppass->flight_id = flight_id;
	ppass->sit_id = sit_id;
	strcpy(ppass->heacard, heacard);
	return ppass;
}
