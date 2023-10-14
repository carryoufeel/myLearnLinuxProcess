#include <stdio.h>

 #include <unistd.h>

int main(int argc, char *argv[])
{
    int ret = rename("./headlink","headlink1");
    if(-1 == ret)
    {
        fprintf(stderr,"rename error");
        return 1;
    }
    return 0;
}
