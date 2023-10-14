
#include <stdio.h>
#include<stdlib.h>



int main(int argc, char *argv[])
{

    printf("1.firefox\n");
    printf("2.calcu\n");
    printf("3.file\n");
    printf("4.quit");


    printf("you choose");
    char tmp[5]={0};
    int num = 0;

    fgets(tmp,sizeof(tmp),stdin);
    num = atoi(tmp);

    switch(num)
    {

    case 1:
        system("firefox www.baidu.com");
        break;
    case 2:
        system("gnome-calculator");
        break;
    case 3:
        system("nautilus /home");
        break;
    case 4:
        exit(1);
    default:
        system("gnome-calculator");

    }



    return 0;
}
