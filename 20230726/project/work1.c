#include<stdio.h>
#include<string.h>
char *Subsrt(const char *s,const char *sub)
{
	int sLen=strlen(s);
	int sublen=strlen(sub);
	int i;
	for(i=0;i<=sLen-sublen;++i)
	{
		if(strncmp(s+i,sub,sublen)==0)
		{
			return (char*)s+i;
		}
	}
	return NULL;
}
int main()
{
	const char *s="Hello china china world america";
	const char *sub="china";
	int counter=0;
	char *ret=Subsrt(s,sub);
	while(ret!=NULL)
	{
		++counter;
		ret=Subsrt(ret+1,sub);
	}
	printf("%d\n",counter);
}
