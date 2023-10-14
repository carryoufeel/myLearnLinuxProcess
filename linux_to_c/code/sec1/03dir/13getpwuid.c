#include <stdio.h>
#include <sys/types.h>
#include <pwd.h>

int main(int argc, char *argv[])
{
    uid_t uid =1000;
    struct passwd *pw = getpwuid(uid);
    if(NULL == pw)
    {
        fprintf(stderr,"getpw error");
        return 1;
    }

    printf("%s %d %s\n ",pw->pw_name ,pw->pw_uid,pw->pw_dir);

    return 0;
}
