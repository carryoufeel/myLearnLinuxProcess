#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    
    struct stat st_buf;
    char path[]="./01ls.c";
    int ret = stat(path,&st_buf);
    if(-1 == ret)
    {
        fprintf(stderr,"stat error");
        return 1;
    }

// 
    //man 7 inode
    if(S_ISREG(st_buf.st_mode))
    {
        fputc('-',stdout);
    }
    else if(S_ISDIR(st_buf.st_mode))
    {
        fputc('d',stdout);
    }
    else if(S_ISCHR(st_buf.st_mode))
    {
        fputc('c',stdout);
    }
    else if(S_ISBLK(st_buf.st_mode))
    {
        fputc('b',stdout);
    }
    else if(S_ISFIFO(st_buf.st_mode)) // pipe
    {
        fputc('p',stdout);
    }
    else if(S_ISLNK(st_buf.st_mode))
    {
        fputc('l',stdout);
    }
    else if(S_ISSOCK(st_buf.st_mode))
    {
        fputc('s',stdout);
    }



    if(S_IRUSR & st_buf.st_mode)
    {
        fputc('r',stdout);
    }
    else
    {
        fputc('-',stdout);
    }

    if(S_IWUSR & st_buf.st_mode)
    {
        fputc('w',stdout);
    }
    else
    {
        fputc('-',stdout);
    }
    if(S_IXUSR & st_buf.st_mode)
    {
        fputc('x',stdout);
    }
    else
    {
        fputc('-',stdout);
    }
// -rw-rw-r-- 1 linux linux  437 Aug  1 09:52 01ls.c
    printf(" %lu %d %d %lu %lu %s\n", st_buf.st_nlink,st_buf.st_uid
           ,st_buf.st_gid,st_buf.st_size,st_buf.st_mtime,path);
    return 0;
}
