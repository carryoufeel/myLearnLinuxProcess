
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
int main(int argc, char *argv[])
{


    FILE* fp = fopen("log","w");
    if(NULL == fp)
    {
        perror("fopen");
        exit(1);
    }
    time_t tm;
    int i = 3;
    pid_t pid = fork();
    if(pid>0)
    {
        
        while(i--)
        {
            time(&tm);
            fprintf(fp,"father pid:%d %s",getpid(),ctime(&tm));
            fflush(fp);
            sleep(3);
        }
    }
    else if(0 == pid)
    {
        while(i--)
        {
            time(&tm);
            fprintf(fp,"child pid:%d %s",getpid(),ctime(&tm));
            fflush(fp);
            sleep(5);
        }
        exit(0);
    }
    else 
    {
        perror("fork");
        exit(1);

    }
    fclose(fp);
    return 0;
}
