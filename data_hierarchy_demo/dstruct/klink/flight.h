#ifndef FLIGHT_H
#define FLIGHT_H
#include <stdio.h>
#include "klink.h"

typedef struct pass{
	klink_node node;
	char name[32];
	int flight_id;
	int sit_id;
	char heacard[32];
}pass_info;

typedef struct flight{
	klink_node node;
	int flight_id;
	char srcadd[32];
	char dstadd[32];
}flight_info;

extern pass_info *creat_pass_date(char *name, int flight_id, int sit_id, char *heacard);
#endif
