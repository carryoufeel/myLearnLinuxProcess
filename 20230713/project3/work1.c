#include<stdio.h>
int main(void)
{
	int a;
	scanf("%d",&a);
	if(a%3!=0)
	{
		printf("%d不能被3整除\n",a);
	}
	else
	{
		printf("%d能被3整除\n",a);
	}
	return 0;
}
