#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void myhandle(int num)
{
    if(SIGUSR1 == num)
    {
        static int i = 0 ;
        printf("老爸在叫你。。。\n");
        if(3 == i)
        {
            signal(SIGUSR1, SIG_IGN);
        }
        i++;
    }
    else if(SIGUSR2 == num)
    {
        static int j = 0;
        printf("老妈在叫你。。。\n");
        if(4 == j)
        {
            signal(SIGUSR2,SIG_DFL);
        }
        j++;

    }
}
int main(int argc, char *argv[])
{

    signal(SIGUSR1,myhandle);
    signal(SIGUSR2,myhandle);
    while(1)
    {
    
        printf("i', play... pid %d\n",getpid());
        sleep(1);
    
    }
    return 0;
}
