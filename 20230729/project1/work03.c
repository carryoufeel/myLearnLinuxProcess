#include<stdio.h>
int main()
{
	FILE *p=fopen("1.txt","r");
	while(1)
	{
		int c=fgetc(p);
		if(c==EOF)
		{
			break;
		}
			printf("%c",(unsigned char)c);
	}
	fclose(p);
	return 0;
}
