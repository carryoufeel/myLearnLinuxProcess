#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc, char *argv[])
{
    pid_t ret = fork();
    if(ret>0)
    {//father
        int i =3;
        while(i--)
        {
            printf("father handling.... pid:%d\n",getpid());
            sleep(1);
        }
        int wstatus;
        pid_t pid = wait(&wstatus);
        printf("recycle pid %d status %d\n",pid,wstatus);
    }
    else if(0 == ret)
    {//child
        int i = 5;
        while(i--)
        {
            printf("child handling ....pid:%d\n",getpid());
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

