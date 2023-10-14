
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    pid_t ret = fork();
    if(ret>0)
    {//father
        while(1)
        {
            printf("发视频\n");
            sleep(1);
        }
    }
    else if(0 == ret)
    {//child
        while(1)
        {
            printf("接受控制\n");
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
