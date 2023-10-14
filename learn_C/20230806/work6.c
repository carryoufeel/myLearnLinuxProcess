#include<stdio.h>
#include<time.h>
int main()
{
	time_t tm;
	time(&tm);
	printf("%s\n",ctime(&tm));
}
