


#include <stdio.h>
#include "mul.h"
#include "add.h"
int main(int argc, char *argv[])
{
    int a = 10;
    int b  = 20;
    int c = 0 ;
    c = add(a,b);
    printf("c is %d\n",c);
    c =sub(a,b);
    printf("c is %d\n",c);
    c = mul(a,b);
    printf("c is %d\n",c);
    c = div(a,b);
    printf("c is %d\n",c);
    return 0;
}
