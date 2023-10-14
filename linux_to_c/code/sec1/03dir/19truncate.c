#include <stdio.h>
#include <unistd.h>
       #include <sys/types.h>


int main(int argc, char *argv[])
{

    int ret = truncate("./1.txt",100);
    if(-1 == ret)
    {
        fprintf(stderr,"truncate error\n");
        return 1;
    }
    return 0;
}
