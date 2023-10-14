#ifndef __FRAMEBUFF_H__
#define __FRAMEBUFF_H__

#include <linux/fb.h>

#define RGB888_MODE				1	
#define RGB565_MODE				2

/* RGB888 格式 */
typedef struct __rgb888__ {
	unsigned char B;				//蓝
	unsigned char G;				//绿
	unsigned char R;				//红
	unsigned char Reserved;			//空
}Rgb888_t;

/* RGB565 格式 */
typedef struct __rgb565__ {
	unsigned short R:5;				//红
	unsigned short G:6;				//绿
	unsigned short B:5;				//蓝
}Rgb565_t;

/* RGB信息类型 */
typedef struct __rgb__ {
	Rgb888_t *pRgb888;				//RGB888显存空间首地址
	Rgb565_t *pRgb565;				//RGB565显存空间首地址	
	int Mode;						//RGB显示模式	1:RGB888   2:RGB565 
	struct fb_var_screeninfo vinfo;	//屏幕信息结构体
}Rgb_t;

extern Rgb_t *FrameBuffInit(const char *pdevname);
extern int FrameBuffDeInit(Rgb_t *pTmpRgb);
extern int DrawOnePixel(Rgb_t *pTmpRgb, int xpos, int ypos, unsigned char TmpR, unsigned char TmpG, unsigned char TmpB);
extern int DrawHorLine(Rgb_t *pTmpRgb, int xpos, int ypos, int width, unsigned char TmpR, unsigned char TmpG, unsigned char TmpB);
extern int DrawVerLine(Rgb_t *pTmpRgb, int xpos, int ypos, int height, unsigned char TmpR, unsigned char TmpG, unsigned char TmpB);
extern int DrawDict(Rgb_t *pTmpRgb, int xpos, int ypos, int width, int height, unsigned char TmpR, unsigned char TmpG, unsigned char TmpB);
extern int FillDict(Rgb_t *pTmpRgb, int xpos, int ypos, int width, int height, unsigned char TmpR, unsigned char TmpG, unsigned char TmpB);
extern int ClearScreen(Rgb_t *pTmpRgb);
extern int DrawBarChart(Rgb_t *pTmpRgb, int xpos, int ypos, int height, int minval, int maxval, double *parray, int len);
extern int DrawOneAscii(Rgb_t *pTmpRgb, int xpos, int ypos, char ch, unsigned char TmpFR, unsigned char TmpFG, unsigned char TmpFB, unsigned char TmpBR, unsigned char TmpBG, unsigned char TmpBB);
extern int DrawString(Rgb_t *pTmpRgb, int xpos, int ypos, char *pstr, unsigned char TmpFR, unsigned char TmpFG, unsigned char TmpFB, unsigned char TmpBR, unsigned char TmpBG, unsigned char TmpBB);
extern int DrawOneHanZi(Rgb_t *pTmpRgb, int xpos, int ypos, char *pstr, unsigned char TmpFR, unsigned char TmpFG, unsigned char TmpFB, unsigned char TmpBR, unsigned char TmpBG, unsigned char TmpBB);
extern int DrawHanZiString(Rgb_t *pTmpRgb, int xpos, int ypos, char *pstr, unsigned char TmpFR, unsigned char TmpFG, unsigned char TmpFB, unsigned char TmpBR, unsigned char TmpBG, unsigned char TmpBB);
extern int DrawBmp(Rgb_t *pTmpRgb, int xpos, int ypos, char *pBmpName);
extern int DrawLine(Rgb_t *pFb, int x0, int y0, int x1, int y1, unsigned char TmpR, unsigned char TmpG, unsigned char TmpB);
extern int ShowRgbInfo(Rgb_t *pTmpRgb, unsigned char *rgbdata, int xpos, int ypos, int width, int height);
extern int VideoShow(Rgb_t *pTmpRgb, const char *VideoDevName, int Width, int Height, int xpos, int ypos);
extern int ReadJPEGFile(const char *jpegData, char *rgbdata, int size);
extern int DrawMouse(Rgb_t *pTmpRgb, int x, int y);
extern int SavePosRgbInfo(Rgb_t *pTmpRgb, int x, int y, int width, int height, Rgb888_t *parray);
extern int RecoveryRgbInfo(Rgb_t *pTmpRgb, int x, int y, int width, int height, Rgb888_t *parray);

#endif
