#include <stdio.h>
#include <unistd.h>
#include "cp.h"
#include <stdlib.h>
#include <sys/wait.h>
void show_cmd()
{
    char path[512]={0};
    getcwd(path,sizeof(path));
    printf("linux@ubuntu:%s$",path);
    fflush(stdout);

}

int mycd(char* path)
{
    int ret = 0 ;
    if(NULL == path)
    {
        ret = chdir("/home/linux");
    }
    else
    {
        ret = chdir(path);
    }
    if(-1 == ret)
    {
        perror("chdir");
        return 1;
    }

    return 0;
}
int mycat(char* filename)
{
    if(NULL == filename)
    {
        return 1;
    }

    int srcfd = open(filename,O_RDONLY);

    if(-1 == srcfd)
    {

        fprintf(stderr,"open error");
        return 1;

    }


    while(1)
    {
        char s[1024]={0};
        int ret = read(srcfd,s,sizeof(s));
        if(ret<=0)
        {
            break;
        }
        printf("%s",s);
        fflush(stdout);
    }
    close(srcfd);
    return 0;

}
int main()
{
    while(1)
    {
        char cmd[512]={0};
        char * args[5]={NULL};
        show_cmd();
        read(0,cmd,sizeof(cmd));// \0
        cmd[strlen(cmd)-1]='\0';
        // cp  1 2
        //ln -s 1 2 NULL
        args[0]= strtok(cmd," ");
        args[1]= strtok(NULL," ");
        args[2]= strtok(NULL," ");
        args[3]= strtok(NULL," ");
        args[4]= strtok(NULL," ");
        if(NULL == args[0])
        {
            continue;
        }
        if(0 == strcmp(args[0],"cd"))
        {
            if(NULL == args[1])
            {
                chdir("/home/linux");
            }
            else
            {

                chdir(args[1]);
            }
            continue;
        }
        pid_t pid = fork();
        if(pid>0)
        {
            wait(NULL);
        }
        else if(0 == pid)
        {
            //ls /home/linux -alhF
            //ls -alhF
            if(0== strcmp(args[0],"ll"))
            {
               args[0] = "ls";
               if(NULL ==args[1])
               {
                args[1]="-alhF";
               }
               else
               {
                   args[2]="-alhF";
               }

            }
            execvp(args[0],args);
            exit(1);
        }
        else
        {
            perror("fork");
            exit(1);

        }



    }

    printf("Hello World!\n");
    return 0;
}
