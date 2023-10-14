#include<stdio.h>
#include<stdlib.h>
int fn(double n)
{
	return n;
}
int div3(int n)
{
	return n%3==0;
}
int div5(int n)
{
	return n%5==0;
}
void printArray(double *a,int len,int(*pfn)(double))
{
	int i=0;
	for(;i<len;i++)
	{
	//	if(pfn(a[i]))
		{
			printf("%lf\t",*(a+i));
		}
	}
	putchar(10);
}
int doublecmp(const void *p1,const void *p2)
{
	double *q1=(double*)p1;
	double *q2=(double*)p2;
	if(*q1>*q2)
	{
		return 1;
	}
	else  if(*q1==*q2)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}

int main()
{
	double a[10]={1,2,3,4,5,6,7,8,9,10};
	qsort(a,10,8,doublecmp);
	printArray(a,10,fn);
}
