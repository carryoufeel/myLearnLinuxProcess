#include<stdio.h>
int main()
{
	FILE *s_1=fopen("sor2.txt","w");
	fputs("Hello\n",s_1);
	fputs("你好\n",s_1);
	fputs("死\n",s_1);
	fclose(s_1);
	FILE *s_2=fopen("sor2.txt","r");
	FILE *d=fopen("des2.txt","w");
	while(1)
	{
		char s[100]={0};
		if(fgets(s,sizeof(s),s_2)==NULL)
		{
			break;
		}
		fputs(s,d);
	}
	fclose(s_2);
	fclose(d);
}
