#include<stdio.h>
int main()
{
	int a,b,c;
	scanf("%d%d%d",&a,&b,&c);
	((a%2==1&&b%2==1&&c%2!=1)||
	 (a%2==1&&b%2!=1&&c%2==1)||
	 (a%2!=1&&b%2==1&&c%2==1))?printf("YES\n"):printf("NO\n");
}
