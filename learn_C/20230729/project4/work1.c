#include<stdio.h>
int main()
{
	FILE *p=fopen("1.txt","r");
	int a[26]={0};
	while(1)
	{
		int i=fgetc(p);
		if(i>='a'&&i<='z')
		{
			a[i-'a']++;
		}
		else if(i==EOF)
		{
			break;
		}
	}
	for(int i=0;i<26;i++)
	{
		printf("%c:%d\n",i+'a',a[i]);
	}
}
