
#include <stdio.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
    
    int ret = chdir("../");
    if(-1 == ret)
    {
        fprintf(stderr,"chdir error");
        return 1;
    }

    FILE* fp = fopen("aaaa","w");
    fclose(fp);
    return 0;
}
