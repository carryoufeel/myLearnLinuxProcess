#include<stdio.h>
int main()
{
	FILE *s_1=fopen("sor1.txt","w");
	fputc('h',s_1);
	fputc('e',s_1);
	fputc('l',s_1);
	fputc('l',s_1);
	fputc('o',s_1);
	fputc(10,s_1);
	fclose(s_1);
	FILE *s_2=fopen("sor1.txt","r");
	FILE *d_1=fopen("des1.txt","w");
	while(1)
	{
		char s;
		s=fgetc(s_2);
		fputc(s,d_1);
		if(EOF==s)
		{
			break;
		}
	}
}
