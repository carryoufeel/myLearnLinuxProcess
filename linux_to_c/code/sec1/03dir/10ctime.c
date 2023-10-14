
#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[])
{
    time_t tm;
    time(&tm);
    printf("%s",ctime(&tm));
    return 0;
}
