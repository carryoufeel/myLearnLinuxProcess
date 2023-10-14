#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include <sys/types.h>
#include <unistd.h>
int main(int argc,char *argv[])
{
	int i=0;
	char s[100]={};
	char c[100]={};
	char a[100]={};
	if(argc>3)
	{
		i=strlen(argv[1]);
		strncpy(s,argv[1],i);
		i=strlen(argv[2]);
		strncpy(c,argv[2],i);
		i=strlen(argv[3]);
		strncpy(a,argv[3],i);
		printf("%d\n",argc);
		execlp(s,s,c,a,NULL);
	}
	else if(argc>2)
	{
		i=strlen(argv[1]);
		strncpy(s,argv[1],i);
		i=strlen(argv[2]);
		strncpy(c,argv[2],i);
		printf("%d\n",argc);
		execlp(s,s,c,NULL);
	}
	else
	{
		i=strlen(argv[1]);
		strncpy(s,argv[1],i);
		execlp(s,c,NULL);
	}
	printf("error\n");
}
