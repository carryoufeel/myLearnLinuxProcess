#include<stdio.h>
#include<string.h>
void swap(char **s,char **c)
{
	char *t;
	t=*s;
	*s=*c;
	*c=t;
}
void reverse(char **s,int len)
{
	for (int i=0;i<len/2;i++)
	{
		swap(s+i,s+len-i-1);
	}
}
void printStrings(char **s,int len)
{
	int i;
	for(i=0;i<len;++i)
	{
		puts(*(s+i));
	}
}
void sort(char **s,int len)
{
	for(int i=0;i<len-1;i++)
	{
		for(int j=i;j<len;j++)
		{
			if(strcmp(*(s+j),*(s+i))<0)
			{
				swap(s+j,s+i);
			}
		}
	}
}
#if 0
int main()
{
	char *s[]={"Hello","China","World"};
	int len=sizeof(s)/sizeof(*s);
	reverse(s,len);
	printStrings(s,len);
}
#endif
int main(int argc,char *argv[])
{
	int i;
	sort(argv,argc);
	reverse(argv,argc);
	printStrings(argv,argc);
}
