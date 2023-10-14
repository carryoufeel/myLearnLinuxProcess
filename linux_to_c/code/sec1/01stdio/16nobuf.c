


#include <stdio.h>

int main(int argc, char *argv[])
{
    
    FILE* fp = fopen("aaa","r");
    if(NULL == fp)
    {
    
        fprintf(stderr,"fopen error");//stdout  stderr
    }
    while(1);
    return 0;
}
