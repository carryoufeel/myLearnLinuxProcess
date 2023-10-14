#include <stdio.h>

// ./aout 
// ./a.out 1.c 2.c 
int main(int argc, char *argv[])
{

    if(argc<3)
    {
        printf("./a.out srcfile dstfile\n");
        return 1;
    }
    FILE* srcfp = fopen(argv[1],"r");
    FILE* dstfp = fopen(argv[2],"w");
    if(NULL == srcfp || NULL == dstfp)
    {
        printf("fopen error\n");
        return 1;
    }

    while(1)
    {
        int ret =  fgetc(srcfp);
        if(EOF == ret)
        {
            break;
        }
        fputc(ret,dstfp);

    }


    fclose(dstfp);
    fclose(srcfp);

    return 0;
}
