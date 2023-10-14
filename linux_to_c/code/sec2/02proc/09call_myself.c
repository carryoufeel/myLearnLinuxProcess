

#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    //firefox www.taobao.com 
    
    //execl("app","app","111","222","333",NULL);
    //ls /home/linux/ ./ --color=auto
    execlp("/home/linux/20230729/sec2/02proc/app","app","111","222","333",NULL);
     char *const args[] = {"ls","/home/linux/","./","--color=auto",NULL};
    //execv("/bin/ls",args);
    //execvp(args[0],args);
    printf("看见就错了\n");
    return 0;
}
