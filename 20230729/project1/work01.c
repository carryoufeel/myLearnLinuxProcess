#include<stdio.h>
int main()
{
	FILE *p=fopen("1.txt","w");
	if(p==NULL)
	{
		printf("no\n");
		return 1;
	}
	return 0;
}
