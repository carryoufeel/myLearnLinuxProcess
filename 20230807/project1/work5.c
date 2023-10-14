#include<stdio.h>
#include <unistd.h>
int main()
{
	char *arg[]={"./work1.out",NULL};
	execv("work1.out",arg);
	printf("wrong\n");
}
