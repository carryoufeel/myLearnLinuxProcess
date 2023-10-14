#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
int main()
{
	DIR *f=opendir("../20230731");
	if(NULL== f)
    {
        fprintf(stderr,"opendir error");
        return 1;
    }
	while(1)
	{
		struct dirent *o=readdir(f);
		if(o==NULL)
		{
			break;
		}
		printf("%s  ",o->d_name);
		switch(o->d_type)
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
	closedir(f);
	}
