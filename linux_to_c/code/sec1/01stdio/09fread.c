#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
typedef struct 
{
    char name[50];
    int age;
    float heigh;
}PERSON;
int main(int argc, char *argv[])
{
    FILE*fp = fopen("1","r");
    if(NULL == fp)
    {
        printf("fopen error\n");
        return 1;
    }

    PERSON per;
    bzero(&per,sizeof(per));//bit zero 
    fread(&per,sizeof(per),1,fp);

    printf("%s %d %f\n",per.name,per.age,per.heigh);

    fclose(fp);
    return 0;
}
