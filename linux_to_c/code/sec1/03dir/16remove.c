#include <stdio.h>

 #include <unistd.h>

int main(int argc, char *argv[])
{
    int ret = remove("softlink");
    if(-1 == ret)
    {
        fprintf(stderr,"rm error");
        return 1;
    }
    return 0;
}
