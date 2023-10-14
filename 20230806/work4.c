#include<stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
int main()
{
	rmdir("./hello");
	DIR *p=opendir("./");
	while(1)
	{
		struct dirent *r=readdir(p);
		if(r==NULL)
		{
			break;
		}
		printf("%s\n",r->d_name);
	}
	closedir(p);
}
