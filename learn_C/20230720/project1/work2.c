#include<stdio.h>
#include<string.h>
void printStrings(char s[][100],int rows)
{
	int i=0;
		for(i=0;i<rows;i++)
		{
			puts(s[i]);
		}
}

int maxOfString(char s[][100],int rows)
{
	int max;
	max=0;
	int i;
	for(i=0;i<rows;i++)
	{
		if(strcmp(s[max],s[i])<0)
		{
			max=i;
		}
	}
	return max;
}
int stringSort(char a[][100],int rows)
{
	for(int i=rows-1;i>0;i--)
	{
		for(int j=0;j<i;j++)
		{
			if(strcmp(a[j],a[j+1])>0)
			{
				char t[100];
				strcpy(t,a[j]);
				strcpy(a[j],a[j+1]);
				strcpy(a[j+1],t);
			}	
		}
	}
}
int binaryFind(char s[][100],int rows,char n[])
{
	int begin=0,end=rows-1;
	int mid;
	while(begin<=end)
	{
		mid=(begin+end)/2;
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
		return mid;
	}
	else
	{
		return -1;
	}
}
int main()
{
	char s[][100]={"hello","world","china"};
	char n[]={"china"};
	gets(n);
	stringSort(s,3);
	printStrings(s,3);
	printf("%d\n",maxOfString(s,3));
	printf("%d\n",binaryFind(s,3,n));
}
