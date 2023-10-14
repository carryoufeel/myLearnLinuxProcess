#include <stdio.h>


int main(int argc, char *argv[])
{
    FILE*fp = fopen("1.txt","w");
    if(NULL == fp)
    {
        printf("fopen error\n");
        return 1;
    }

    int ret = fputc('h',fp);
    if(EOF ==ret)
    {
        printf("fputc error\n");
        return 1;
    }
     fputc('e',fp);
     fputc('l',fp);
     fputc('l',fp);
     fputc('o',fp);

    fclose(fp);
    return 0;
}
