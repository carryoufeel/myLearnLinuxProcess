#include "Mouse.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, const char *argv[])
{
	pthread_t tid_mouse;

	pthread_create(&tid_mouse, NULL, MouseThread, NULL);
	
	while (1)
	{
		printf("(%d, %d)\n", curx, cury);
		if (LeftButtonPress)
		{
			printf("Left Button Pressed!\n");
			sleep(1);
		}

		if (RightButtonPress)
		{
			printf("RightButtonPress!\n");
			sleep(1);
		}
	}

	pthread_join(tid_mouse, NULL);
	
	return 0;
}
