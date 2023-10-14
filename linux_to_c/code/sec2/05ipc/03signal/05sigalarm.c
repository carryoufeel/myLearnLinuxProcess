
    
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
int flag = 0 ;
void handle(int num)
{

    flag = !flag;
    alarm(3);
}
int main(int argc, char *argv[])
{
    signal(SIGALRM,handle);    
    alarm(3);
    while(1)
    {
        if(0 == flag)
        {
            printf("i'm sleep\n");
        }
        else if(1 == flag)
        {
            printf("i'm working\n");
        }
        sleep(1);
    }
    return 0;
}
