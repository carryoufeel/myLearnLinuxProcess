

#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    //firefox www.taobao.com 
    
    execl("/usr/bin/firefox","firefox","www.taobao.com",NULL);
    
    printf("看见就错了\n");
    return 0;
}
