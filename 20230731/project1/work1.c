#include<stdio.h>
int main()
{
	FILE *p=fopen("1.txt","r");
	long i=0,j=0;
	fseek(p,0,SEEK_END);
	i=ftell(p);
	rewind(p);
	j=ftell(p);
	printf("%ld,%ld\n",i,j);
	fclose(p);
}
