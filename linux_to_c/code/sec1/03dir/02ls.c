#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>


int main(int argc, char *argv[])
{
    DIR* dir = opendir("../02fileio"); 
    if(NULL== dir)
    {
        fprintf(stderr,"opendir error");
        return 1;
    }

    while(1)
    {
        struct dirent * info = readdir(dir);
        if(NULL == info)
        {
            break;
        }
        printf("%s ",info->d_name);
        switch(info->d_type)
        {
            case DT_BLK:
                printf("block file\n");
                break;
            case DT_CHR:
                printf("char file\n");
                break;
            case DT_DIR:
                printf("dir file\n");
                break;
            case DT_FIFO:
                printf("fifo file\n");
                break;
            case DT_REG:
                printf("REG file\n");
                break;
            default:
                printf("\n");
        }
    }

    closedir(dir);
    return 0;
}
