#include <stdio.h>


int main(int argc, char *argv[])
{
    FILE*fp = fopen("1.txt","r");
    if(NULL == fp)
    {
        printf("fopen error\n");
        return 1;
    }

    char buf[256]={0};
    fgets(buf,sizeof(buf),fp);

    printf("%s\n",buf);

    fclose(fp);

    return 0;
}
