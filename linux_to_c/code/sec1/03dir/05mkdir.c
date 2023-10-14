
#include <stdio.h>

#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    int ret = mkdir("123",0777);    
    if(-1 == ret)
    {
        fprintf(stderr,"mkdir error");
        return 1;
    }
    return 0;
}
