
#include <stdio.h>

int main(int argc, char *argv[])
{
    //1
    printf("hello");
    fflush(stdout);
    
    int i =0;
    for(i =0 ;i<1024;i++)
    {
        fputc('a',stdout);
    }
   
    fflush(stdout);
    while(1);
    return 0;
}
