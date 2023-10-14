#include<stdio.h>
#include<string.h>
int main()
{
	char a[3][100]={"hello","world","china"};
	char max[100];
	strcpy(max,a[0]);
	for(int i=0;i<3;i++)
	{
		if(strcmp(max,a[i])<0)
		{
			strcpy(max,a[i]);
		}
	}
	puts(max);
}
