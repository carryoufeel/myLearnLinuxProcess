
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
        sleep(3);
        close(fd[0]);
        char buf[10]="hello";
        // SIGPIPE gdb 
        write(fd[1],buf,strlen(buf)+1);
        close(fd[1]);
    }
    else if(0 == pid)
    {
        close(fd[1]);
        close(fd[0]);
    }
    else
    {
        perror("fork");
        exit(1);
    }
    return 0;
}
