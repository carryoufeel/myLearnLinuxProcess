#include <stdio.h>


int main(int argc, char *argv[])
{
    FILE*fp = fopen("1.txt","w");
    if(NULL == fp)
    {
        printf("fopen error\n");
        return 1;
    }

    printf("input string:");
    char buf[50]={0};
    scanf("%s",buf);
    int ret = fputs(buf,fp);//"aslkdfjlsadfjlkjsa\n\0"
    if(EOF == ret)
    {
        printf("fputs error");
        return 1;
    }

    fclose(fp);

    return 0;
}
