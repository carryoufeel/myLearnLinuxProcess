#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char *argv[])

{
    int aaa = 123810923;
    int fd = open("1.txt",O_WRONLY|O_CREAT|O_TRUNC,0666);
    if(-1 == fd)
    {
    
        fprintf(stderr,"open error");
        return 1;
        
    }
    return 0;
}
