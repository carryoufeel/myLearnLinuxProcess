
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
            printf("发视频\n");
            sleep(1);
        }
    }
    else if(0 == ret)
    {//child
        while(i--)
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
    
    printf("aaa\n");
    return 0;
}
