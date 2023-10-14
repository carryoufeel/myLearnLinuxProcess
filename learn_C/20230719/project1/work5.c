#include<stdio.h>
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

int ohMyStrlen(char *s)
{
	int i=0;
	while(s[i])
	{
		i++;
	}
	return i;
}

void strlow(char *s)
{
	int i=0;
	while(s[i])
	{
		if(s[i]>='A'&&s[i]<='Z')
		{
			s[i]+=32;
		}
		++i;
	}
}

void strupper(char *s)
{
	int i=0;
	while(s[i])
	{
		if(s[i]>='a'&&s[i]<='z')
		{
			s[i]-=32;
		}
		++i;
	}
}

void ohMyStrcpy(char *dest,char *src)
{
	int i=0;
	while(src[i])
	{
		dest[i]=src[i];
		i++;
	}
	dest[i]=0;
}

void ohMyStrcat(char *dest,char *src)
{
	int i=0;
	while(dest[i])
	{
		i++;
	}
	int j=0;
	while(src[j])
	{
		dest[i]=src[j];
		i++;
		j++;
	}
	dest[i]=0;
}
int ohMyStrcmp(char *s1,char *s2)
{
	int i=0;
	while(s1[i]==s2[i]&&s1[i]&&s2[i])
	{
		++i;
	}
	return s1[i]-s2[i];
}
void strRevers(char *s)
{
	int len=ohMyStrlen(s);
	for(int i=0;i<len/2;i++)
	{
		char t=s[i];
		s[i]=s[len-i-1];
		s[len-i-1]=t;
	}
}

int main()
{
	char s1[100]="Hello World!";
	char s2[100]="China ";
	//printf("%d\n",Strlen(s1));
	//strlow(s1);
	//strupper(s1);
	//ohMyStrcpy(s2,s1);
	//ohMyStrcat(s2,s1);
	strRevers(s1);
	ohMyPuts(s1);
	//printf("%d\n",ohMyStrcmp(s1,s2));
}
