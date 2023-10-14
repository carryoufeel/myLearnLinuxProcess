#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include "FrameBuff.h"
#include "Log.h"
#include "Mouse.h"

#define MOUSE_STARTX	40
#define MOUSE_STARTY	54
#define MOUSE_ENDX		65494
#define MOUSE_ENDY		65480

Rgb_t *pTmpRgb = NULL;

void LeftButtonFun(void)
{
	int tmpx = 0;
	int tmpy = 0;

	LogWrite("左键按下!\n");
	TransferOfAxes(40, 54, 65494, 65480, curx, cury, pTmpRgb->vinfo.xres, pTmpRgb->vinfo.yres, &tmpx, &tmpy);
	
	if ((tmpx >= 120 && tmpx <= 120 + 250) && (tmpy >= 180 && tmpy <= 260))
	{
		LogWrite("显示实时信息\n");
	}

	return;
}

int main(int argc, const char *argv[])
{
	pthread_t tid_mouse;
	int tmpx = 0;
	int tmpy = 0;

	LogInit();
	LogWrite("=========================================\n\n\n\n");
	LogWrite(" 软件开始运行\n\n\n\n");
	LogWrite("=========================================\n");
	pTmpRgb = FrameBuffInit("/dev/fb0");
	
	ClearScreen(pTmpRgb);
	DrawBmp(pTmpRgb, 0, 0, "images/HomePage.bmp");

	MouseLeftButtonClicked = LeftButtonFun;
	pthread_create(&tid_mouse, NULL, MouseThread, NULL);

	curx = (MOUSE_ENDX - MOUSE_STARTX) / 2;
	cury = (MOUSE_ENDY - MOUSE_STARTY) / 2;

	while (1)
	{
		TransferOfAxes(40, 54, 65494, 65480, curx, cury, pTmpRgb->vinfo.xres, pTmpRgb->vinfo.yres, &tmpx, &tmpy);
		DrawMouse(pTmpRgb, tmpx, tmpy);
	}
	pthread_join(tid_mouse, NULL);

#if 0
	/* 视频显示示例 */
	VideoShow(pTmpRgb, "/dev/video0", 320, 240, 0, 0);
#endif

	FrameBuffDeInit(pTmpRgb);
	LogDeInit();
		
	return 0;
}
