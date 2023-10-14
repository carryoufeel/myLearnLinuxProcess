#ifndef __MOUSE_H__
#define __MOUSE_H__

#define MOUSE_DEVNAME	"/dev/input/event2"

/* 鼠标左键按下事件 */
extern void (*MouseLeftButtonClicked)(void);

/* 鼠标右键按下事件 */
extern void (*MouseRightButtonClicked)(void);

extern unsigned int curx;
extern unsigned int cury;
extern unsigned int LeftButtonPress;
extern unsigned int RightButtonPress;
extern void *MouseThread(void *arg);
extern int TransferOfAxes(int VirStartx, int VirStarty, int VirEndx, int VirEndy, int curx, int cury, int RealScreenWidth, int RealScreenHeight, int *pdstx, int *pdsty);
extern int IsNewPosition(int curx, int cury, int dstx, int dsty, int width, int height);


#endif
