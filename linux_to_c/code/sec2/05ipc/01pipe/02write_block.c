
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>              /* Obtain O_* constant definitions */
#include <string.h>

int main(int argc, char *argv[])
{
    int fd[2];
    int ret = pipe(fd);    
    if(-1 == ret)
    {
        perror("pipe");
        exit(1);
    }


    pid_t pid = fork();
    if(pid>0)
    {
        close(fd[0]);
        int i = 0 ;
        char buf[1024]={0};
        for(i = 0 ;i<65;i++)
        {
        
            write(fd[1],buf,1024);
            printf("i:%d\n",i);
        }
        close(fd[1]);
    }
    else if(0 == pid)
    {
        close(fd[1]);
        char buf[1024]={0};

        sleep(5);
        read(fd[0],buf,sizeof(buf));

        close(fd[0]);
    }
    else
    {
        perror("fork");
        exit(1);
    }
    return 0;
}
