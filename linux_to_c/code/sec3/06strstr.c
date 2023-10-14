#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
    int fd = open("./1.txt",O_RDONLY);
    if(-1 == fd)
    {
        perror("open");
        return 1;
    }

    char buf[1024]={0};
    read(fd,buf,sizeof(buf));
    close(fd);
    
    char *args[5]={NULL};

    args[0]= strstr(buf,"days");
    args[1]=strstr(args[0],"week");
    args[2]=strstr(args[1],"citynm");
    args[3]=strstr(args[2],"temperature");
    args[4]=strstr(args[3],"weather");

    args[0] +=7;
    strtok(args[0],"\"");

    args[1]+=7;
    strtok(args[1],"\"");


    args[2]+=9;
    strtok(args[2],"\"");
    
    
    args[3]+=14;
    strtok(args[3],"\"");

    args[4]+=10;
    char* tmp = index(args[4],'"');
    *tmp = '\0';

    printf("%s:%s:%s:%s:%s\n",args[0],args[1],args[2],args[3],args[4]);





    return 0;
}
