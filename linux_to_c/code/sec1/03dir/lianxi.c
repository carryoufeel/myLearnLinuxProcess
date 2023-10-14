#include <stdio.h>
#include <dirent.h>
#include <string.h>
int isnumdir(char* filename)
{

    while(*filename)
    {
    
        if(*filename >='0' && *filename <='9')
        {
            filename++;
            continue;
        }
        else 
        {
            return 0;
        }
    }

    return 1;
}
int show_status(char * filename)
{

    FILE* fp = fopen(filename,"r");
    if(NULL == fp)
    {
        perror("fopen ");
        return 1;
    }

    while(1)
    {
        char buf[128]={0};
        if(fgets(buf,sizeof(buf),fp))
        {
        
            char * args[2]={0};
            args[0]= strtok(buf,":");
            args[1]= strtok(NULL,"\n");

            if(0 == strcmp(args[0],"Name"))
            {
                printf("name:%s ",args[1]);
            }
            if(0 == strcmp(args[0],"State"))
            {
                printf("state:%s ",args[1]);
            }
            if(0 == strcmp(args[0],"Pid"))
            {
                printf("pid:%s ",args[1]);
            }
            if(0 == strcmp(args[0],"Uid"))
            {
                args[1]=strtok(args[1],"\t");
                printf("Uid:%s ",args[1]);
            }
        

        }
        else
        {
           break; 
        }

    }
    fclose(fp);

}
int main(int argc, char *argv[])
{
    DIR* dir = opendir("/proc");

    if(NULL == dir)
    {

        perror("opendir");
        return 1;
    }
    while(1)
    {

        struct dirent *info =  readdir(dir);
        if(NULL == info)
        {
            break;
        }
        //printf("%s\n",info->d_name);
        if(DT_DIR == info->d_type )
        {
            if(isnumdir(info->d_name))
            {
            
                // /proc/1/status 
                char pathname[512]={0};
                sprintf(pathname,"/proc/%s/status",info->d_name);
               // printf("%s\n",pathname);
                show_status(pathname);
                printf("\n");
            
            }
        }
    }

    closedir(dir);
    return 0;
}
