

#include <stdio.h>
#include <string.h>


int main(int argc, char *argv[])
{
    int i= 0;

    for(i = 0 ;i<512;i++)
    {
    
        printf("%d %s\n",i,strerror(i) );
    }
    return 0;
}
