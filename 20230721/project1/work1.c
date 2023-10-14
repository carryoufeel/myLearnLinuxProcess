#include<stdio.h>
#include<math.h>
#define S(a,b,c) (((a)+(b)+(c)) / 2.0)
#define AREA(a,b,c)  (sqrt(S(a,b,c)*(S(a,b,c)- (a))*(S(a,b,c)-b)*(S(a,b,c)-c)))
int main()
{
	printf("%f\n",AREA(3,4,5));
}
