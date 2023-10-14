#include<stdio.h>
int main()
{
	FILE *p=fopen("2.txt","r");
	char buf[100]={0};
	fgets(buf,sizeof(buf),p);
	printf("%s\n",buf);
	fclose(p);
}
