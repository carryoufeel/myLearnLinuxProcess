#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(void)
{
	long i;
	int k;
	unsigned int n;
	n = time(NULL);
	srandom(n);
	for(k=0;k<10;k++)
	{
		i = random() % 50 + 50;
		printf("%ld\n",i);
	}
	return 0;
}
