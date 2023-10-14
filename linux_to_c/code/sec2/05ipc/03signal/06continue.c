



#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
void handle(int num)
{
}


int main(int argc, char *argv[])
{
    signal(SIGCONT,handle);
    int i = 10 ;
    while(i--)
    {
    

        printf("i'm sleep pid:%d\n",getpid());
        sleep(1);
        if(5 == i )
        {
            pause();
        }
    }
    return 0;
}
