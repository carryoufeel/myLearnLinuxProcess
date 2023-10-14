
#include <stdio.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
 
    char path[512]={0};
    getcwd(path,sizeof(path));
    printf("first path %s\n",path);
    int ret = chdir("../");
    if(-1 == ret)
    {
        fprintf(stderr,"chdir error");
        return 1;
    }

    getcwd(path,sizeof(path));
    printf("second path %s\n",path);
    FILE* fp = fopen("aaaa","w");
    fclose(fp);
    return 0;
}
