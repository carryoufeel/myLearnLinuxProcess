#include <stdio.h>


int main(int argc, char *argv[])
{
    FILE*fp = fopen("1.txt","r");
    if(NULL == fp)
    {
        printf("fopen error\n");
        return 1;
    }
    while(1)
    {
        int c = fgetc(fp);
        if(EOF ==  c )
        {
            break;
        }
        printf("%c",(unsigned char)c);

    }
    printf("\n");

    fclose(fp);
    return 0;
}
