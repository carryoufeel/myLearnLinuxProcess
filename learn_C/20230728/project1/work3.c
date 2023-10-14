#include<stdio.h>
int main()
{
	int i=0xFFFFFFFF;
	int j=0;
	for(j=0;j<32;++j)
	{
		if(j%3==0)
		{
			i&=~(1<<j);
		}
	}
	printf("%x\n",i);
}
