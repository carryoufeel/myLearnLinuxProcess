#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>


int main(int argc, char *argv[])
{
    DIR* dir = opendir("../02fileio"); 
    if(NULL== dir)
    {
        fprintf(stderr,"opendir error");
        return 1;
    }

    while(1)
    {
        struct dirent * info = readdir(dir);
        if(NULL == info)
        {
            break;
        }
        printf("%s\n",info->d_name);
    }

    closedir(dir);
    return 0;
}
