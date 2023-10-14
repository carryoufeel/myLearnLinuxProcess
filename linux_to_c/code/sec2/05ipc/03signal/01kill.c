#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
//kill -9 1000
//./a.out 1000
int main(int argc, char *argv[])
{
    if(argc<2)
    {
        printf("./a.out pid\n");
        return 0;
    }
    pid_t pid = atoi(argv[1]);
    int ret = kill(pid,SIGKILL);    
    if(-1 == ret)
    {
        perror("kill");
        return 1;
    }
    return 0;
}
