#include<stdio.h>
int main()
{
	int i=100;
	int counter=0;
	//if(1&(i>>7))
	//{
	//	puts("yes");
	//}
	//else
	//{
	//	puts("no");
	//}
	for(int j=0;j<32;j++)
	{
		if((i>>j)&1)
		{
			counter++;
		}
	}
	printf("%d\n",counter);
}
