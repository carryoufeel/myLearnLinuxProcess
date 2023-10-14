
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    pid_t ret = fork();
    if(ret>0)
    {//father
        int i  =20;
        while(i--)
        {
            printf("发视频\n");
            sleep(1);
        }
    }
    else if(0 == ret)
    {//child
        int i =5;
        while(i--)
        {
            printf("接受控制\n");
            sleep(1);
        }
        exit(0);
    }
    else
    {
    
        perror("fork");
        return 1;
    }
    return 0;
}
