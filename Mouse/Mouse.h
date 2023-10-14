#ifndef __MOUSE_H__
#define __MOUSE_H__

#define MOUSE_DEVNAME	"/dev/input/event2"

extern unsigned int curx;
extern unsigned int cury;
extern unsigned int LeftButtonPress;
extern unsigned int RightButtonPress;
extern void *MouseThread(void *arg);

#endif
