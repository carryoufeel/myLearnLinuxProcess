#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    
    struct stat st_buf;
    int ret = stat("./01ls.c",&st_buf);
    if(-1 == ret)
    {
        fprintf(stderr,"stat error");
        return 1;
    }

    printf("ino:%lu mode:%d link:%lu uid:%d gid:%d size:%lu time:%lu\n",st_buf.st_ino,st_buf.st_mode
           ,st_buf.st_nlink,st_buf.st_uid, st_buf.st_gid, st_buf.st_size,st_buf.st_mtime);

    return 0;
}
