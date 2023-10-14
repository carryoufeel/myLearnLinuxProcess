
#include <stdio.h>

int main(int argc, char *argv[])
{
    
    FILE* fp = fopen("./1.txt","r");
    if(NULL == fp)
    {
        printf("fopen error\n");
        return 1;
    }

    fseek(fp,5,SEEK_SET);
    char buf[50];
    fgets(buf,sizeof(buf),fp);
    printf("%s",buf);
    fclose(fp);
    return 0;
}
