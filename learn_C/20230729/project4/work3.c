#include<stdio.h>
int main()
{
	FILE *p=fopen("work2.c","r");
	int a=0;
	while(1)
	{
		char s[100]={0};
		if(fgets(s,sizeof(s),p)==NULL)
		{
			break;
		}
		a++;
	}
	printf("%d\n",a);
}
