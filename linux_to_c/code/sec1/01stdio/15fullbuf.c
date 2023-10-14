
#include <stdio.h>

int main(int argc, char *argv[])
{
    FILE* fp = fopen("./1.txt","w");
    if(NULL == fp)
    {
        printf("fopen error\n");
        return 1;
    }

/*
    char buf[50]="到此一游";
    fputs(buf,fp);
*/

    int i = 0 ;
    for(i = 0 ;i<4096;i++)
    {
        fputc('a',fp);
    }
    fflush(fp);
    while(1);
    return 0;
}
