
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
  
    int n =5;

    int i = 0 ;
    for(i = 0 ;i<n;i++)
    {
    
        pid_t pid = fork();
        if(pid>0)
        {
            printf("father pid %d\n",getpid());
        }
        else if(0 == pid)
        {
            printf("child pid %d\n",getpid());
            exit(0);
        }
        else 
        {
            perror("fork");
            exit(1);

        }
    }
    return 0;
}
