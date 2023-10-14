
#include <stdio.h>
#include <error.h>
#include <errno.h> //extern int errno;
int main(int argc, char *argv[])
{
    FILE* fp = fopen("1234","r");
    if(NULL == fp)
    {
    
      //  perror("fopen line6");
      error(1,errno,"func:%s linenum:%d file:%s\n",__func__,__LINE__,__FILE__);
        return 1;
    }
    return 0;
}
