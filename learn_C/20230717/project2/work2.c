#include<stdio.h>
int main()
{
	char s[]="ushwihuHSUHBCHYBSX";
	int l=sizeof(s)/sizeof(s[0]);
	int i=0,j=0;
	for(;i<l;i++)
	{
		if(s[i]>='a'&&s[i]<='z')
		{
			j+=1;
		}
	}
	printf("%d\n",j);
}
