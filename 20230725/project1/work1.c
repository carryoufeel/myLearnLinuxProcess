#include<stdio.h>
int ohMyStrlen(const char *p)
{
	int i=0;
	while(*p!='\0')
	{
		i++;
		p++;
	}
	return i;
}

void ohMyStrncpy(char *des,char *src,int n)
{
	while(*src&&n!=0)
	{
		*des++=*src++;
		n--;
	}
	*des=0;
}

void ohMyStrncat(char *des,char *src,int n)
{
		n--;
	while(*des!=0)
	{
		des++;
	}
	while(*src&&n!=0)
	{
		*des++=*src++;
		n--;
	}
	*des='\0';
}

int ohMyStrncmp(const char *a,const char *b,int n)
{
	while(*a&&*b&&--n&&*a==*b)
	{
		a++;
		b++;
		n--;
	}
	return *a-*b;
}

int newStrlenByRecursion(char *p)
{
	if (*p=='\0')
	{
		return 0;
	}
	else
	{
		return newStrlenByRecursion(p+1)+1;
	}
}

		n--
int ohMyStrcmp(char *a,char *b)
{
	while(*a==*b&&*a&&*b)
	{
		++a;
		++b;
	}
	return *a-*b;
}

void ohMyStrcat(char *des,const char *src)
{
	while(*des!='\0')
	{
		des++;
	}
	while(*src!='\0')
	{
		*des=*src;
		des++;
		src++;
	}
	*des=0;
}

void ohMyStrcpy(char *des,char *src)
{
	while(*src!='\0')
	{
		*des=*src;
		des++;
		src++;
	}
	*des=0;
}

void newStrcpyByRecursion(char *des,char *src)
{
	if(*src=='\0')
	{
		*des=0;
		return ;
	}
	else
	{
		*des=*src;
		newStrcpyByRecursion(des+1,src+1);
	}

}

void ohMyPuts(char *p)
{
	while(*p!='\0')
	{
		putchar(*p);
		++p;
	}
	putchar(10);
}

void newPutsByRecursion(char *p)
{
	if(*p=='\0')
	{
		putchar(10);
		return ;
	}
	else
	{
		putchar(*p);
		p++;
		newPutsByRecursion(p);
	}
}

int main()
{
	char s[100]="hello world";
	char y[100];
	//ohMyStrcpy(y,s);
	//newStrcpyByRecursion(y,s);
	//ohMyStrcat(y,s);
	ohMyStrncpy(y,s,5);
	//ohMyPuts(y);
	ohMyStrncat(y,s,3);
	newPutsByRecursion(y);
	printf("%d\n",ohMyStrncmp("Hello","HeChina",1));
	//printf("%d\n",newStrlenByRecursion(s));
	//printf("%d\n",ohMyStrcmp(s,y));
}
