
#include <stdio.h>

int main(int argc, char *argv[])
{
    
    FILE* fp = fopen("./1.txt","r+");
    if(NULL == fp)
    {
        printf("fopen error\n");
        return 1;
    }

    fseek(fp,1024*1024*1024,SEEK_END);

    char buf[50]="到此一游";
    fputs(buf,fp);
    fclose(fp);
    return 0;
}
