#include<stdio.h>
int main()
{
	int a[i][j]={0};
	int i=0,j=1,k=1;
	a[i][j]=k;
	int x=0,y=0;
	for(;k<10;k++)
	{
		int x=i;
		int y=j;
		i++;
		j++;
		if(i=0)
		{
			if(a[i][j]==0)
			{
				i=2;
			}
			else
			{
				i=x;
				j=y;
			}
		}
		else(j=2)
		{
			if(a[i][j]==0)
                        {
                                j=0;
                        }
                        else
                        {
                                i=x;
                                j=y;
				continue;
		}	}
	}
	printf()
}
