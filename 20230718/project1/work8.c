#include<stdio.h>
#include<string.h>
int main()
{
	char s[][100]={"hello","world","china","yes","fuck"};
	char n[100];
	gets(n);
	int rows=sizeof(s)/sizeof(s[0]);
	int i,j;
	for(i=0;i<rows-1;++i)
	{
		for(j=i+1;j<rows;++j)
			if(strcmp(s[i],s[j])>0)
			{
				char t[100];
				strcpy(t,s[i]);
				strcpy(s[i],s[j]);
				strcpy(s[j],t);
			}
	}
	for(i=0;i<rows;i++)
	{
		puts(s[i]);
	}
	int begin=0,end=rows-1;
	while(begin<=end)
	{	
		int mid = (begin + end) / 2;
		if(strcmp(s[mid],n)>0)
		{
			end=mid-1;
		}
		else if(strcmp(s[mid],n)<0)
		{
			begin=mid+1;
		}
		else
		{
			break;
		}
	}
	if(begin<=end)
	{
		printf("yes\n");
	}
	else
	{
		printf("no\n");
	}
	//for(i=0;i<rows;++i)
	//{
	//	puts(s[i]);
	//}
}
