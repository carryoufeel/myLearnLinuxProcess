#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])

{
    int fd = open("1.txt",O_RDONLY);
    if(-1 == fd)
    {
    
        fprintf(stderr,"open error");
        return 1;
        
    }
    char buf[512]={0};
   int ret =  read(fd,buf,sizeof(buf));
   if(-1 == ret)
   {
        
        fprintf(stderr,"read error");
        return 1;
   }
   printf("ret %d\n buf :%s\n",ret,buf);

   close(fd);

    return 0;
}
