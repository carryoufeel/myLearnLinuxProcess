#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE* fp = fopen("1.txt","w");
    if(NULL == fp)
    {
        perror("fopen");
        exit(1);
    }
    printf("hello");
    fputs("hello",fp);
    // _exit(1);
    exit(1);

    printf("end\n");
    return 0;
}
