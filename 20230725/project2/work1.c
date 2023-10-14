#include<stdio.h>
int subStr(char *pStr,char *pWord)
{
	int n=0;
	while(*pWord)
	{
		n++;
		pWord++;
		if(*pWord==*pStr)
		{
			while(*pWord&&*pStr&&*pWord==*pStr)
			{
				pWord++;
				pStr++;
				if(*pStr==0)
				{
					return n;
				}
			}
		}
	}
}
int main()
{
	printf("%d\n",subStr("hello","fdsahelfdashellofdashellofdashellofdashellohello"));
}
