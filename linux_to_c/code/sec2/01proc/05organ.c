
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    pid_t ret = fork();
    if(ret>0)
    {//father
        int i  =5;
        while(i--)
        {
            printf("father pid:%d ppid:%d\n",getpid(),getppid());
            sleep(1);
        }
        exit(0);
    }
    else if(0 == ret)
    {//child
        int i =10;
        while(i--)
        {
            printf("child pid:%d ppid:%d\n",getpid(),getppid());
            sleep(1);
        }
    }
    else
    {
    
        perror("fork");
        return 1;
    }
    return 0;
}
