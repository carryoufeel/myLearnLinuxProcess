
#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[])
{
    time_t tm;
    time(&tm);
    printf("%ld\n",tm);
    return 0;
}
