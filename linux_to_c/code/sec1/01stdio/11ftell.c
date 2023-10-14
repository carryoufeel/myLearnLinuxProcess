
#include <stdio.h>

int main(int argc, char *argv[])
{
    
    FILE* fp = fopen("./1.txt","r");
    if(NULL == fp)
    {
        printf("fopen error\n");
        return 1;
    }

    fseek(fp,0,SEEK_END);
    long size = ftell(fp);
    printf("1.txt size %ld",size);
    fclose(fp);
    return 0;
}
