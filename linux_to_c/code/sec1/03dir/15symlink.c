#include <stdio.h>

 #include <unistd.h>

int main(int argc, char *argv[])
{
    int ret = link("./01ls.c","head");
    if(-1 == ret)
    {
        fprintf(stderr,"link error");
        return 1;
    }
    return 0;
}
