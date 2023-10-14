#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>
int show_detail(char path[])
{
    struct stat st_buf;
    int ret = stat(path,&st_buf);
    if(-1 == ret)
    {
        fprintf(stderr,"stat error %s\n",path);
        return 1;
    }

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


    struct group *gr = getgrgid(st_buf.st_gid);
    if(NULL == gr)
    {
        fprintf(stderr,"get gr error");
        return 1;
    }
    struct passwd *pw = getpwuid(st_buf.st_uid);
    if(NULL == pw)
    {
        fprintf(stderr,"get pw error");
        return 1;
    }
    struct tm *tm_info = localtime(&st_buf.st_mtime);
    if(NULL == tm_info)
    {
    
        fprintf(stderr,"get time error");
        return 1;
    }
// -rw-rw-r-- 1 linux linux  437 Aug  1 09:52 01ls.c
    printf(" %lu %s %s %lu %d %d %d:%d %s\n", st_buf.st_nlink,pw->pw_name 
           ,gr->gr_name,st_buf.st_size,tm_info->tm_mon,tm_info->tm_mday,
           tm_info->tm_hour,tm_info->tm_min,path);

}
// ./a.out         ./a.out /home/linux

int main(int argc, char *argv[])
{

    DIR* dir ;
    char path[512]={0};
    if(NULL != argv[1])
    {
        strcpy(path,argv[1]);
    }
    else
    {
        getcwd(path,sizeof(path));
    }
    dir= opendir(path); 
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
        //printf("%s\n",info->d_name);
        // ./a.out  /home/linux 
        // ../     1.c   ../1.c  strcat 
       
        char newpath[512]={0};
        sprintf(newpath,"%s/%s",path,info->d_name);
        show_detail(newpath);
        
    }

    closedir(dir);
    return 0;
}
