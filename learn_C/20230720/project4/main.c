#include<stdio.h>
#include"leapYear.h"
#include"days.h"
int main()
{
    int year,month;
    scanf("%d%d",&year,&month);
    printTitle(year,month);
    prinfDays(year,month);
}

