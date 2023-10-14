

#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    //firefox www.taobao.com 
    
    //execl("/usr/bin/firefox","firefox","www.taobao.com",NULL);
    //ls /home/linux/ ./ --color=auto
    //execlp("ls","ls","/home/linux/","./","--color=auto",NULL);
     char *const args[] = {"ls","/home/linux/","./","--color=auto",NULL};
    execv("/bin/ls",args);
    printf("看见就错了\n");
    return 0;
}
