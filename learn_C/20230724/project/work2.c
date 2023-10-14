#include<stdio.h>
void maxAndMin(int a,int b,int c,int *max,int *min)
{
	*max=a>b?a:b;
	*max=*max>c?*max:c;
	*min=a<b?a:b;
	*min=*min<c?*min:c;
}
int main()
{
	int max,min;
	maxAndMin(10,20,30,&max,&min);
	printf("%d,%d\n",max,min);
}
