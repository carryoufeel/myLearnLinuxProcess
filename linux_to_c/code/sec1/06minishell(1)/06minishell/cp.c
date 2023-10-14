#include "cp.h"

int mycp(char* srcfile,char* dstfile)
{

    if(NULL == srcfile || NULL == dstfile)
    {
        return 1;
    }

    int srcfd = open(srcfile,O_RDONLY);
    int dstfd = open(dstfile,O_WRONLY|O_CREAT|O_TRUNC,0666);
    if(-1 == srcfd|| -1 == dstfd)
    {

        fprintf(stderr,"open error");
        return 1;

    }


    while(1)
    {
        char s[1024]={0};
        int ret = read(srcfd,s,sizeof(s));
        if(ret<=0)
        {
            break;
        }
        write(dstfd,s,ret );
    }
    close(srcfd);
    close(dstfd);
    return 0;

}
