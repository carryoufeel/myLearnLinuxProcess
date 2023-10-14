
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void * getmemory()
{
    return malloc(100);
}
char * p;
void clear()
{

    printf("这里是清理函数, %s\n",p);
    free(p);

}
int main(int argc, char *argv[])
{
    
    p = (char*)getmemory();
    atexit(clear);
    strcpy(p,"hello");

    printf("before exit();");
    exit(1);
    

    
    return 0;
}
