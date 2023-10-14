#include <stdio.h>


int main(int argc, char *argv[])
{
    FILE*fp = fopen("1.txt","w");
    if(NULL == fp)
    {
        printf("fopen error\n");
        return 1;
    }

    return 0;
}
