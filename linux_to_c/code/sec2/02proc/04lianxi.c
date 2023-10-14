#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    int j = 0 ;
    pid_t pid[10]={0};
    for(j = 0 ;j<10;j++)
    {
        pid[j]= fork();
        //ret = fork();
        if(pid[j]>0)
        {//father
        }

        else if(0 == pid[j])
        {//child

            pid[j] = getpid();
            int i = rand()%3+1;
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
    }
    int inx=3;
    int wstatus;
    //非阻塞回收
    while(1)
    {
        pid_t recycle = waitpid(pid[inx],&wstatus,WNOHANG);
        if(pid[inx] == recycle)
        {
            if(WIFEXITED(wstatus))// normal
            {
                printf("回收成功,pid:%d\n",recycle);
            }
            break;
        }
        //子进程没有结束
        else if( 0 == recycle)
        {
            printf("子进程未结束\n");
            sleep(1);
        }
        else 
        {
            printf("child pid error\n");
            break;
        }

    }
    return 0;//exit(0)
}

