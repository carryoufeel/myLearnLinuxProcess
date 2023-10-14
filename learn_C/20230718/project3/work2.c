#include<stdio.h>
int theMaxOfTheTwoNumbers(int a,int b)
{
	int max;
	max=a>b?a:b;
}

int theSmallOfTheTwoNumber(int a,int b)
{
	int small;
	small=a<b?a:b;
}

int theLeastCommonMulitipleOfTheTwoNumber(int a,int b)
{
	int c=theMaxOfTheTwoNumbers(a,b);
	for(;c<1000000;c++)
	{
		if(c%a==0&&c%b==0)
		{
			return c;
			break;
		}
	}
}

int theGreatestCommonDivisorOfTwoNumber(int a,int b)
{
	int c=theSmallOfTheTwoNumber(a,b);
	for(;c>0;c--)
	{
		if(a%c==0&&b%c==0)
		{
			return c;
			break;
		}
	}
}

int main()
{
	int a,b;
	scanf("%d%d",&a,&b);
	printf("最大公约数为%d\n",theGreatestCommonDivisorOfTwoNumber(a,b));
	printf("最小公倍数为%d\n",theLeastCommonMulitipleOfTheTwoNumber(a,b));
}
