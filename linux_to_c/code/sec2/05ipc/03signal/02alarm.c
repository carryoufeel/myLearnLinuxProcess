
    
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    
    alarm(3);
    while(1)
    {
    
        printf("i'm sleep\n");
        sleep(1);
    }
    return 0;
}
