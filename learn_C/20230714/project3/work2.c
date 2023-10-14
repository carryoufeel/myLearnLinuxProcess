#include<stdio.h>
#include<math.h>
int main()
{
	int a,b,c,i,k=0;
	for(i=100;i<1000;++i)
	{
		a=i/100;
		b=(i-a*100)/10;
		c=i%10;
		if(i==pow(a,3)+pow(b,3)+pow(c,3))
		{
			printf("%d\t",i);
			++k;
		}
	}
	printf("\n有%d个水仙花数\n",k);
}
