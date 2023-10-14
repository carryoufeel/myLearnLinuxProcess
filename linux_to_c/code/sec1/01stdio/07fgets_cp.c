#include <stdio.h>


int main(int argc, char *argv[])
{
    if(argc<3)
    {
        printf("./a.out srcfile dstfile\n");
        return 1;
    }
    FILE* srcfp = fopen(argv[1],"r");
    FILE* dstfp = fopen(argv[2],"w");
    if(NULL == srcfp|| NULL == dstfp)
    {
        printf("fopen error\n");
        return 1;
    }
    char buf[512]={0};
    while(1)
    {
        if(NULL==fgets(buf,sizeof(buf),srcfp))
        {
            break;
        }
        fputs(buf,dstfp);
    }


    fclose(srcfp);
    fclose(dstfp);

    return 0;
}
