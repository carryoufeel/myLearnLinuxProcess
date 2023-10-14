/*************************************************************************
	> File Name: days.c
	> Author: yas
	> Mail: rage_yas@hotmail.com
	> Created Time: Thu 20 Jul 2023 02:00:27 AM PDT
 ************************************************************************/

#include<stdio.h>
#include"leapYear.h"
#include"days.h"
int totalDay(int year, int month)
{
    int i=0,j=0,days=0;
    for(i=year-1;i>=1900;--i)
    {
	    days+=leapYear(i);
    }
    for(j=month-1;j>=1;--j)
    {
        days+=Monthday(year,j);
    }
 
    return days;
}
int beforeMonthWeek(int year,int month)
{
    int i=0;
    i=totalDay(year,month)%7;
    return i;
}

void printTitle(int year,int month)
{
    printf("%dyear%dmonth\n",year,month);
    printf("mon\ttue\twed\tthu\tfri\tsat\tsun\n");
}

void prinfDays(int year,int month)
{
    int d=Monthday(year,month),j=0;
    for(int i=beforeMonthWeek(year,month);i>0;--i)
    {
        printf("\t");
	j++;
    }
    for(int c=1;c<=d;c++)
    {
        printf("%d\t",c);
        j++;
        if(j==7)
        {
            printf("\n");
            j=0;
        }
    }
    putchar(10);
}
