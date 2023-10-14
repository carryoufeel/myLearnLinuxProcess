#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char *argv[])

{
    if(argc<3)
    {
        printf("./a.out srcfile dstfile\n");
        return 1;
    }

    int srcfd = open(argv[1],O_RDONLY);
    int dstfd = open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,0666);
    if(-1 == srcfd|| -1 == dstfd)
    {

        fprintf(stderr,"open error");
        return 1;

    }
   // char s[512];
    char * s =(char*) malloc(1024*1024*10);
    if(NULL == s)
    {
        printf("malloc error");
        return 1;
    }

    while(1)
    {
        int ret = read(srcfd,s,1024*1024*10);
        if(ret<=0)
        {
            break;
        }
        write(dstfd,s,ret );
    }
    close(srcfd);
    close(dstfd);
    free(s);


    return 0;
}
