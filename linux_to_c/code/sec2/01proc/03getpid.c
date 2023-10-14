
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int i =10;
    pid_t ret = fork();
    if(ret>0)
    {//father
        while(i--)
        {
            printf("father pid:%d ppid:%d\n",getpid(),getppid());
            sleep(1);
        }
    }
    else if(0 == ret)
    {//child
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
    
    printf("aaa pid:%d ppid:%d\n",getpid(),getppid());
    return 0;
}
