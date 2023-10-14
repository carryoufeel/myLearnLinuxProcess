#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
    char name[50];
    int age;
    float heigh;
}PERSON;
int main(int argc, char *argv[])
{
    FILE*fp = fopen("1","w");
    if(NULL == fp)
    {
        printf("fopen error\n");
        return 1;
    }

    PERSON per;
    bzero(&per,sizeof(per));//bit zero 
    // FILE*  stdin  stdout  stderr
    printf("input name");
    fgets(per.name,sizeof(per.name),stdin);//zhangsan\0\0

    per.name[strlen(per.name)-1]='\0';
    char tmp[10];//100\n\0
    printf("input age");
    fgets(tmp,sizeof(tmp),stdin);
    per.age = atoi(tmp);
    
    
    printf("input heigh");
    fgets(tmp,sizeof(tmp),stdin);
    per.heigh = atof(tmp);


   int ret =  fwrite(&per,sizeof(per),1,fp);
   if(ret != 1)
   {
    printf("fwrite error\n");
    return 1;
   }



    fclose(fp);
    return 0;
}
