
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void handle(int num)
{
    pid_t recycle = wait(NULL);
    printf("wait pid%d\n",recycle);
}
int main(int argc, char *argv[])
{

    signal(SIGCHLD,handle);
    int i = 5 ;
    while(i--)
    {
    
        pid_t pid = fork();
        if(pid>0)
        {
            printf("father pid:%d\n",getpid());
            sleep(1);
        }

        else if(0 == pid)
        {
            printf("child pid:%d\n",getpid());
            int t = rand()%3;
            sleep(t);
            exit(0);
        }
        else
        {
        
            perror("fork");
            return 1;
        }
    }
    return 0;
}
