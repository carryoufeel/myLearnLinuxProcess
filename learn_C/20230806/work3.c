#include <sys/stat.h>
#include <sys/types.h>
#include<stdio.h>
#include <dirent.h>
int main()
{
	mkdir("./hello",0777);
	DIR *p=opendir("./");
	while(1)
	{
		struct dirent *o=readdir(p);
		if(o==NULL)
		{
			break;
		}
		printf("%s\n",o->d_name);
	}
	closedir(p);
}
