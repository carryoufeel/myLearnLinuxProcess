#include <stdio.h>

 #include <unistd.h>

int main(int argc, char *argv[])
{
    int ret = symlink("./01ls.c","softlink");
    if(-1 == ret)
    {
        fprintf(stderr,"symlink error");
        return 1;
    }
    return 0;
}
