#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
int main(int argc, char *argv[])
{
    int fd = open("1.txt",O_RDONLY);
    if(-1 == fd)
    {
        fprintf(stderr,"open error");
        return 1;
    }
    
    FILE* fp = fdopen(fd,"r");
    if(NULL == fp)
    {
        
        fprintf(stderr,"fdopen error");

        return 1;
    }
    char buf[512]={0};
    fgets(buf,sizeof(buf),fp);
    printf("%s",buf);
    fflush(stdout);
    
    fclose(fp);
    return 0;
}
