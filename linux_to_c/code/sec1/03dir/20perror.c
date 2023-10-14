
#include <stdio.h>

int main(int argc, char *argv[])
{
    FILE* fp = fopen("1234","r");
    if(NULL == fp)
    {
    
        perror("fopen line6");
        return 1;
    }
    return 0;
}
