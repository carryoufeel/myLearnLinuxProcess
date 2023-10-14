#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
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
        //非阻塞回收
        while(1)
        {
            pid_t pid = waitpid(ret,&wstatus,WNOHANG);
            if(pid == ret)
            {
                if(WIFEXITED(wstatus))// normal
                {
                    printf("recycle pid %d return val %d\n",pid,WEXITSTATUS(wstatus));
                }
                else if(WIFSIGNALED(wstatus))// unnormal
                {

                    printf("recycle pid %d signal num %d\n",pid,WTERMSIG(wstatus));

                }
                break;
            }
            //子进程没有结束
            else if( 0 == pid)
            {
                printf("子进程未结束\n");
               // sleep(1);
            }
            else 
            {
                printf("child pid error\n");
                break;
            }

        }
    }

    else if(0 == ret)
    {//child
        int i = 30;
        while(i--)
        {
            printf("child handling ....pid:%d\n",getpid());
            sleep(1);
        }
        exit(20);
    }
    else
    {

        perror("fork");
        return 1;
    }
    return 0;//exit(0)
}

