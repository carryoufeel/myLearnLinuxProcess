
#include <stdio.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
    int ret = rmdir("123");    
    if(-1 == ret)
    {
        fprintf(stderr,"rmdir error");
        return 1;
    }
    return 0;
}
