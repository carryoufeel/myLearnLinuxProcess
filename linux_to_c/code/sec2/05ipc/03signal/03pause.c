



#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
    int i = 10 ;
    while(i--)
    {
    

        printf("i'm sleep\n");
        sleep(1);
        if(5 == i )
        {
            pause();
        }
    }
    return 0;
}
