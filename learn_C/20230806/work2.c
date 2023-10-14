#include<stdio.h>
#include<unistd.h>
int main()
{
	char puth[1024]={};
	getcwd(puth,sizeof(puth));
	puts(puth);
	chdir("../");
	getcwd(puth,sizeof(puth));
	puts(puth);

}
