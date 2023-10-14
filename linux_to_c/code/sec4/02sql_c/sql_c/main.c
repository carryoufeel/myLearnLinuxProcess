#include <stdio.h>
#include <sqlite3.h>
//gcc 1.c -lsqlite3
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
    char sql_cmd[1024]="insert into user values(5,'ccc',25);";
    ret = sqlite3_exec(db,sql_cmd,NULL,NULL,&errmsg);
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
