#include <stdio.h>
#include <sys/types.h>
#include <grp.h>



int main(int argc, char *argv[])
{
    gid_t gid  =1000;
    struct group *gr = getgrgid( gid);
    if(NULL == gr)
    {
    
        fprintf(stderr,"getgr gid error");
        return 1;
    }

    printf("%s %d\n",gr->gr_name,gr->gr_gid);


    int i = 0 ;
    while(gr->gr_mem[i])
    {
        printf("%s\n",gr->gr_mem[i++]);
    }

    return 0;
}
