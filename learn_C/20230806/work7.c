#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[])
{
	time_t tm;
	time(&tm);
	struct tm * tm_info = localtime(&tm);
	printf("%d-%d-%d %d:%d:%d\n",tm_info->tm_year+1900,tm_info->tm_mon+1,tm_info->tm_mday
			,tm_info->tm_hour,tm_info->tm_min,tm_info->tm_sec);
	return 0;
}
