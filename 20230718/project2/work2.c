#include<stdio.h>
int daysOfTheMonth(int y,int m)
{
	int d;
	if(m==1||m==3||m==5||m==7||m==8||m==10||m==12)
	{
		d=31;
	}
	else if(m==4||m==6||m==9||m==11)
	{
		d=30;
	}
	else if(y%4==0&&y%100!=0||y%400==0)
	{
		d=29;
	}
	else
	{
		d=28;
	}
	return d;
}
int main()
{
	int m,d,y;
	printf("请输入年份和月份\n");
	scanf("%d%d",&y,&m);
	d=daysOfTheMonth(y,m);
	printf("%d年%d月有%d天\n",y,m,d);
}
