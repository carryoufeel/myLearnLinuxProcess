#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    FILE* fp = fopen("1.txt","r");
    if(NULL == fp)
    {
        fprintf(stderr,"fopen error");
        return 1;
    }
    
    int fd = fileno(fp);
    if(-1 == fd)
    {
        
        fprintf(stderr,"fileno error");

        return 1;
    }
    char buf[512]={0};
    read(fd,buf,sizeof(buf)-1);
    printf("%s",buf);
    fflush(stdout);
    
    fclose(fp);
    return 0;
}
