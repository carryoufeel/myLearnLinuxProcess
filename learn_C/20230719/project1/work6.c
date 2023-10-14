#include<stdio.h>
void ohMyItoa(char *desc,int a)
{
	int i=0,n=0;
	int k=a;
	if(a<0)
	{
		a=0-a;
	}
	while(a)
	{
		n=a%10;
		desc[i]=n+48;
		i++;
		a/=10;
	}
	if(k<a)
	{
		desc[i++]='-';
	}
	desc[i]=0;

}
int ohMyStrlen(char *s)
{
	int i=0;
	while(s[i])
	{
		i++;
	}
	return i;
}
void ohMyStrRevers(char *s)
{
	int len=ohMyStrlen(s);
	for(int i=0;i<len/2;i++)
	{
		char t=s[i];
		s[i]=s[len-i-1];
		s[len-i-1]=t;
	}
}
void ohMyPuts(char *s)
{
	int i=0;
	while(s[i])
	{
		putchar(s[i]);
		i++;
	}
	putchar(10);
}

int main()
{
	int a=0;
	char s[100];
	scanf("%d",&a);
	ohMyItoa(s,a);
	ohMyStrRevers(s);
	ohMyPuts(s);
}
