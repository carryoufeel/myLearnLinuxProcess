/*************************************************************************
	> File Name: leapYear.c
	> Author: yas
	> Mail: rage_yas@hotmail.com
	> Created Time: Thu 20 Jul 2023 01:03:58 AM PDT
 ************************************************************************/

#include"leapYear.h"
int Monthday(int years,int month)
{
    int days=0;
    if(month==1||month==3||month==5||month==7||month==8||month==10||month==12)
    {
	    days=31;
    }
    else if(month==4||month==6||month==9||month==11)
    {
	    days=30;
    }
    else if(years%4==0&&years%100!=0||years%400==0)
    {
	    days=29;
    }
    else
    {
            days=28;
    }
    return days;
}
int leapYear(int years)
{
	int i,day=0;
	for(i=1;i<13;i++)
	{
		day+=Monthday(years,i);
	}
	return day;
}

