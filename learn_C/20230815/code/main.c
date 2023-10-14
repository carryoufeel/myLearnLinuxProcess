#include<stdio.h>
#include"futureweathe.h"
#include"realtimeweather.h"
#include"tips.h"
#include"askhead.h"
int main()
{
		printf("欢迎使用实时天气查询系统\n");
		printf("========================\n");
		printf("请在输入“1”后输入城市名\n");
		printf("2、查询实施天气\n");
		printf("3、未来一周的天气\n");
		printf("4、出行生活指数\n");
		printf("5、退出\n");
	while(1)
	{
		int p=0;
		scanf("%d",&p);
		if(p==2)
		{
			realtimeweather();
		}
		else if(p==3)
		{
			futureweather();
		}
		else if(p==4)
		{
			tips();
		}
		else if(p==5)
		{
			break;
		}
		else if (p==1) 
		{
			askhead();
		}
	}
}
