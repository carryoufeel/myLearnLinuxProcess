#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void myhandle1(int num)
{
    static int i = 0 ;
    printf("老爸在叫你。。。\n");
    if(3 == i)
    {
        signal(SIGINT, SIG_IGN);
    }
    i++;
}
void myhandle2(int num)
{
    static int i = 0;
    printf("老妈在叫你。。。\n");
    if(4 == i)
    {
        signal(SIGQUIT,SIG_DFL);
    }
    i++;
}
int main(int argc, char *argv[])
{

    signal(SIGINT,myhandle1);
    signal(SIGQUIT,myhandle2);
    while(1)
    {
    
        printf("i', play...\n");
        sleep(1);
    
    }
    return 0;
}
