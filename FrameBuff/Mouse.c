#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h>  
#include <string.h>  
#include <sys/types.h>  
#include <fcntl.h>  
#include <errno.h>  
#include <time.h>  
#include <linux/input.h>  
#include "Mouse.h"

struct input_event event;  
unsigned int curx;
unsigned int cury;
unsigned int LeftButtonPress;
unsigned int RightButtonPress;
void (*MouseLeftButtonClicked)(void);
void (*MouseRightButtonClicked)(void);


/***********************************************************
 *
 * 坐标位置转换 
 *
 * 参数:
 *		VirStartx: 鼠标读取的左上角的x坐标
 *		VirStarty: 鼠标读取的左上角的y坐标
 *		VirEndx: 鼠标读取的右下角的x坐标
 *		VirEndy: 鼠标读取的右下角的y坐标 
 *		curx: 鼠标当前的x坐标
 *		cury: 鼠标当前的y坐标
 *		RealScreenWidth: 当前屏幕的宽度
 *		RealScreenHeight: 当前屏幕的高度
 *		pdstx: 获得的真实屏幕中的x的位置
 *		pdsty: 获得的真实屏幕中的y的位置
 *
 * *********************************************************/

int TransferOfAxes(int VirStartx, int VirStarty, int VirEndx, int VirEndy, int curx, int cury, int RealScreenWidth, int RealScreenHeight, int *pdstx, int *pdsty)
{	
	*pdstx = (double)(curx - VirStartx) * ((double)RealScreenWidth / (VirEndx - VirStartx));
	*pdsty = (double)(cury - VirStarty) * ((double)RealScreenHeight / (VirEndy - VirStarty));

	return 0;
}

void *MouseThread(void *arg)
{  
    char          name[64];           /* RATS: Use ok, but could be better */  
    char          buf[256] = { 0, };  /* RATS: Use ok */  
    unsigned char mask[EV_MAX/8 + 1]; /* RATS: Use ok */  
    int           version;  
    int           fd = 0;  
    int           rc;  
    int           i, j;  
    char          *tmp;  

#define test_bit(bit) (mask[(bit)/8] & (1 << ((bit)%8)))  

#if 0
    for (i = 0; i < 32; i++) {  
        sprintf(name, "/dev/input/event%d", i);  
        if ((fd = open(name, O_RDONLY, 0)) >= 0) {  
            ioctl(fd, EVIOCGVERSION, &version);  
            ioctl(fd, EVIOCGNAME(sizeof(buf)), buf);  
            ioctl(fd, EVIOCGBIT(0, sizeof(mask)), mask);  
            printf("%s\n", name);  
            printf("    evdev version: %d.%d.%d\n",  
                   version >> 16, (version >> 8) & 0xff, version & 0xff);  
            printf("    name: %s\n", buf);  
            printf("    features:");  
            for (j = 0; j < EV_MAX; j++) {  
                if (test_bit(j)) {  
                    const char *type = "unknown";  
                    switch(j) {  
                    case EV_KEY: type = "keys/buttons"; break;  
                    case EV_REL: type = "relative";     break;  
                    case EV_ABS: type = "absolute";     break;  
                    case EV_MSC: type = "reserved";     break;  
                    case EV_LED: type = "leds";         break;  
                    case EV_SND: type = "sound";        break;  
                    case EV_REP: type = "repeat";       break;  
                    case EV_FF:  type = "feedback";     break;  
                    }  
                    printf(" %s", type);  
                }  
            }  
            printf("\n");  
            close(fd);  
        }  
    }  
#endif

        sprintf(name, "%s", MOUSE_DEVNAME);  
        if ((fd = open(name, O_RDWR, 0)) >= 0) {  
//            printf("%s: open, fd = %d\n", name, fd);  
            for (i = 0; i < LED_MAX; i++) {  
                event.time.tv_sec  = time(0);  
                event.time.tv_usec = 0;  
                event.type         = EV_LED;  
                event.code         = i;  
                event.value        = 0;  
                write(fd, &event, sizeof(event));  
            }  

            while ((rc = read(fd, &event, sizeof(event))) > 0) {  
/*	               printf("%-24.24s.%06lu type 0x%04x; code 0x%04x;"  
                       " value 0x%08x; ",  
                       ctime(&event.time.tv_sec),  
                       event.time.tv_usec,  
                       event.type, event.code, event.value);  
					   */
                switch (event.type) {  
                case EV_KEY:  
                    if (event.code > BTN_MISC) {  
//                        printf("Button %d %s", event.code & 0xff, event.value ? "press" : "release");  
//						printf("code:%d, value:%d\n", event.code & 0xff, event.value);

						if ((16 == (event.code & 0xff)) && event.value)
						{
							/* 左键按下 */
							LeftButtonPress = 1;
							if (MouseLeftButtonClicked != NULL)
							{
								MouseLeftButtonClicked();
							}
						}
						else if ((16 == (event.code & 0xff)) && !event.value)
						{
							/* 左键抬起 */
							LeftButtonPress = 0;
						}

						if ((17 == (event.code & 0xff)) && event.value)
						{
							/* 右键按下 */
							RightButtonPress = 1;
							if (MouseRightButtonClicked != NULL)
							{
								MouseRightButtonClicked();
							}
						}
						else if ((17 == (event.code & 0xff)) && !event.value)
						{
							/* 右键抬起 */
							RightButtonPress = 0;
						}

                    } else {  
//                        printf("Key %d (0x%x) %s", event.code & 0xff, event.code & 0xff, event.value ? "press" : "release");  
                    }  
                    break;  
                case EV_REL:  
                    switch (event.code) {  
                    case REL_X:      tmp = "X";       break;  
                    case REL_Y:      tmp = "Y";       break;  
                    case REL_HWHEEL: tmp = "HWHEEL";  break;  
                    case REL_DIAL:   tmp = "DIAL";    break;  
                    case REL_WHEEL:  tmp = "WHEEL";   break;  
                    case REL_MISC:   tmp = "MISC";    break;  
                    default:         tmp = "UNKNOWN"; break;  
                    }  
                    printf("Relative %s %d", tmp, event.value);  
                    break;  
                case EV_ABS:  
                    switch (event.code) {  
                    case ABS_X:        tmp = "X";        break;  
                    case ABS_Y:        tmp = "Y";        break;  
                    case ABS_Z:        tmp = "Z";        break;  
                    case ABS_RX:       tmp = "RX";       break;  
                    case ABS_RY:       tmp = "RY";       break;  
                    case ABS_RZ:       tmp = "RZ";       break;  
                    case ABS_THROTTLE: tmp = "THROTTLE"; break;  
                    case ABS_RUDDER:   tmp = "RUDDER";   break;  
                    case ABS_WHEEL:    tmp = "WHEEL";    break;  
                    case ABS_GAS:      tmp = "GAS";      break;  
                    case ABS_BRAKE:    tmp = "BRAKE";    break;  
                    case ABS_HAT0X:    tmp = "HAT0X";    break;  
                    case ABS_HAT0Y:    tmp = "HAT0Y";    break;  
                    case ABS_HAT1X:    tmp = "HAT1X";    break;  
                    case ABS_HAT1Y:    tmp = "HAT1Y";    break;  
                    case ABS_HAT2X:    tmp = "HAT2X";    break;  
                    case ABS_HAT2Y:    tmp = "HAT2Y";    break;  
                    case ABS_HAT3X:    tmp = "HAT3X";    break;  
                    case ABS_HAT3Y:    tmp = "HAT3Y";    break;  
                    case ABS_PRESSURE: tmp = "PRESSURE"; break;  
                    case ABS_DISTANCE: tmp = "DISTANCE"; break;  
                    case ABS_TILT_X:   tmp = "TILT_X";   break;  
                    case ABS_TILT_Y:   tmp = "TILT_Y";   break;  
                    case ABS_MISC:     tmp = "MISC";     break;  
					case ABS_MT_SLOT:  tmp = "MT_SLOT";     break;  
					case ABS_MT_TRACKING_ID: tmp = "MT_TRACKING_ID";     break;  
					case ABS_MT_POSITION_X:  tmp = "MT_X";     break;  
					case ABS_MT_POSITION_Y:  tmp = "MT_Y";     break;  
                    default:           tmp = "UNKNOWN";  break;  
                    }  
//                    printf("Absolute %s %d", tmp, event.value);  
#if 1
					if (!strcmp(tmp, "X"))
					{
						curx = event.value;
					}
					if (!strcmp(tmp, "Y"))
					{
						cury = event.value;
					}
#endif
                    break;  
                case EV_MSC: printf("Misc"); break;  
                case EV_LED: printf("Led");  break;  
                case EV_SND: printf("Snd");  break;  
                case EV_REP: printf("Rep");  break;  
                case EV_FF:  printf("FF");   break;  
                    break;  
                }  
                printf("\n");  
            }  
            printf("rc = %d, (%s)\n", rc, strerror(errno));  
            close(fd);  
        }  
    return 0;  
}

/* 鼠标是否更新位置 */
int IsNewPosition(int curx, int cury, int dstx, int dsty, int width, int height)
{
	if (abs(dstx - curx) <= width && abs(dsty - cury) <= height)
	{
		return 0;
	}
		
	return 1;
}
