#include <stdio.h>
#include <sqlite3.h>
//gcc 1.c -lsqlite3
int show(void*arg,int col,char**result,char**title)
{
    static int flag =  0;
    int i = 0;
    if(0 == flag)
    {
        for(i = 0 ;i <col;i++)
        {
            printf("%s\t",title[i]);
        }
        printf("\n");
        flag = 1;
    }

    for(i = 0 ;i <col;i++)
    {
        printf("%s\t",result[i]);
    }
    printf("\n");
    //must
    return 0;
}
int main()
{
    sqlite3* db=NULL;
    char* errmsg=NULL;
    int ret = sqlite3_open("/home/linux/20230729/sec4/01sqlite3/test.db",&db);
    if(SQLITE_OK != ret)
    {
        fprintf(stderr,"open db, %s\n",sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;

    }
    char sql_cmd[1024]="select * from user;";
    ret = sqlite3_exec(db,sql_cmd,show,NULL,&errmsg);
    if(SQLITE_OK != ret)
    {
        fprintf(stderr,"exec db %s, %s\n",sql_cmd,errmsg);
        sqlite3_free(errmsg);
        sqlite3_close(db);
        return 1;

    }
    sqlite3_close(db);

    printf("Hello World!\n");
    return 0;
}
