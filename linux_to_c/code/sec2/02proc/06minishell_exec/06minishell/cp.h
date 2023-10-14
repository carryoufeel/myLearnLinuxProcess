#ifndef CP_H
#define CP_H
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

extern int mycp(char* srcfile,char* dstfile);

#endif // CP_H
