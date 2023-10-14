/*********************************************
 *
 * 界面显示功能代码 
 * FrameBuff.c 
 *
 *********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/videodev2.h>
#include <jpeglib.h>
#include "FrameBuff.h"
#include "Log.h"
#include "font.h"
#include "Mouse.h"


/* FrameBuff初始化 */
Rgb_t *FrameBuffInit(const char *pdevname)
{
	int ret = 0;
	int fb = 0;
	Rgb_t *pTmpRgb = NULL;
	void *pFrameBuff = NULL;
	
	pTmpRgb = malloc(sizeof(*pTmpRgb));
	if (NULL == pTmpRgb)
	{
		LogWrite("malloc rgb info failed\n");
		return NULL;
	}

	/* 打开设备 */
	fb = open(pdevname, O_RDWR);
	if (-1 == fb)
	{
		LogWrite("open %s device failed\n", pdevname);
		return NULL;
	}

	/* 获得屏幕信息 */
	ret = ioctl(fb, FBIOGET_VSCREENINFO, &pTmpRgb->vinfo);
	if (-1 == ret)
	{
		LogWrite("get FrameBuff Screen info failed\n");
		return NULL;
	}

	LogWrite("================== screen info ==================\n");
	LogWrite("xres:%d\n", pTmpRgb->vinfo.xres);
	LogWrite("yres:%d\n", pTmpRgb->vinfo.yres);
	if (pTmpRgb->vinfo.bits_per_pixel / 8 == 4)
	{
		pTmpRgb->Mode = RGB888_MODE;
		LogWrite("This is RGB888 Standard\n");
	}
	else if (pTmpRgb->vinfo.bits_per_pixel / 8 == 2)
	{
		pTmpRgb->Mode = RGB565_MODE;
		LogWrite("This is RGB565 Standard\n");
	}
	LogWrite("======================================\n");
	
	/* 映射显存空间 */
	pFrameBuff = mmap(NULL, pTmpRgb->vinfo.xres_virtual * pTmpRgb->vinfo.yres_virtual * pTmpRgb->vinfo.bits_per_pixel / 8, PROT_READ | PROT_WRITE, MAP_SHARED, fb, 0);
	if (NULL == pFrameBuff)
	{
		LogWrite("FrameBuff Mmap Failed\n");
		return NULL;
	}

	if (pTmpRgb->Mode == RGB888_MODE)
	{
		pTmpRgb->pRgb888 = pFrameBuff;
	}
	else if (pTmpRgb->Mode == RGB565_MODE)
	{
		pTmpRgb->pRgb565 = pFrameBuff;
	}

	return pTmpRgb;
}

/* 绘制一个像素点颜色信息 */
int DrawOnePixel(Rgb_t *pTmpRgb, int xpos, int ypos, unsigned char TmpR, unsigned char TmpG, unsigned char TmpB)
{
	Rgb888_t *pTmp = NULL;

	if (pTmpRgb->Mode == RGB888_MODE)
	{
		pTmp = pTmpRgb->pRgb888;
	}

	pTmp += ypos * pTmpRgb->vinfo.xres_virtual;
	pTmp += xpos;
	
	pTmp->R = TmpR;
	pTmp->G = TmpG;
	pTmp->B = TmpB;

	return 0;
}

/* 绘制一条横线 */
int DrawHorLine(Rgb_t *pTmpRgb, int xpos, int ypos, int width, unsigned char TmpR, unsigned char TmpG, unsigned char TmpB)
{
	int i = 0;

	for (i = 0; i < width; i++)
	{
		DrawOnePixel(pTmpRgb, xpos+i, ypos, TmpR, TmpG, TmpB);
	}

	return 0;
}

/* 绘制一条竖线 */
int DrawVerLine(Rgb_t *pTmpRgb, int xpos, int ypos, int height, unsigned char TmpR, unsigned char TmpG, unsigned char TmpB)
{
	int i = 0;

	for (i = 0; i < height; i++)
	{
		DrawOnePixel(pTmpRgb, xpos, ypos+i, TmpR, TmpG, TmpB);
	}

	return 0;
}

/* 绘制矩形边框 */
int DrawDict(Rgb_t *pTmpRgb, int xpos, int ypos, int width, int height, unsigned char TmpR, unsigned char TmpG, unsigned char TmpB)
{
	DrawHorLine(pTmpRgb, xpos, ypos, width, TmpR, TmpG, TmpB);
	DrawHorLine(pTmpRgb, xpos, ypos+height, width, TmpR, TmpG, TmpB);
	DrawVerLine(pTmpRgb, xpos, ypos, height, TmpR, TmpG, TmpB);
	DrawVerLine(pTmpRgb, xpos+width, ypos, height, TmpR, TmpG, TmpB);

	return 0;
}

/* 填充矩形 */
int FillDict(Rgb_t *pTmpRgb, int xpos, int ypos, int width, int height, unsigned char TmpR, unsigned char TmpG, unsigned char TmpB)
{
	int i = 0;

	for (i = 0; i < height; i++)
	{
		DrawHorLine(pTmpRgb, xpos, ypos+i, width, TmpR, TmpG, TmpB);
	}

	return 0;
}

/* 清屏 */
int ClearScreen(Rgb_t *pTmpRgb)
{
	FillDict(pTmpRgb, 0, 0, pTmpRgb->vinfo.xres, pTmpRgb->vinfo.yres, 0, 0, 0);

	return 0;
}

/* FrameBuff 销毁 */
int FrameBuffDeInit(Rgb_t *pTmpRgb)
{
	if (pTmpRgb != NULL)
	{
		free(pTmpRgb);
	}

	return 0;
}

/***************************************************
 * 绘制柱状图
 * pTmpRgb:显存空间首地址
 * xpos:原点位置(柱状图左下角位置)
 * ypos:原点位置(柱状图左下角位置)
 * height:柱状图高度
 * minval:最小值
 * maxval:最大值
 * parray:数据数组的首地址
 * len:数据的个数 
 **************************************************/
int DrawBarChart(Rgb_t *pTmpRgb, int xpos, int ypos, int height, int minval, int maxval, double *parray, int len)
{	
	unsigned char Red[3] = {255, 0, 0};
	unsigned char Green[3] = {0, 255, 0};
	unsigned char Blue[3] = {0, 0, 255};
	unsigned char Yellow[3] = {255, 255, 0};
	unsigned char Purple[3] = {255, 0, 255};
	unsigned char *pCol[5] = {Red, Green, Blue, Yellow, Purple};
	int i = 0;
	double DataVal = 0;
	int Dict_xpos = 0;
	int Dict_ypos = 0;

	for (i = 0; i < len; i++)
	{	
		DataVal = parray[i];

		Dict_xpos = xpos + i * 20;
		Dict_ypos = ypos - (DataVal / (maxval - minval) * height);
		
		FillDict(pTmpRgb, Dict_xpos, Dict_ypos, 20, ypos - Dict_ypos, pCol[i][0], pCol[i][1], pCol[i][2]);
		LogWrite("Dict_xpos:%d Dict_ypos:%d Width:20 Height:%d R:%d G:%d B:%d\n", Dict_xpos, Dict_ypos, Dict_ypos-ypos, pCol[i][0], pCol[i][1], pCol[i][2]);
	}
	
	return 0;
}

/* 绘制一个ASCII码 */
int DrawOneAscii(Rgb_t *pTmpRgb, int xpos, int ypos, char ch, unsigned char TmpFR, unsigned char TmpFG, unsigned char TmpFB, unsigned char TmpBR, unsigned char TmpBG, unsigned char TmpBB)
{
	unsigned char zimo[16] = {0};
	int i = 0;
	int j = 0;
	unsigned char flag = 0;

	memcpy(zimo, &fontdata_8x16[ch*16], 16);

	for (j = 0; j < 16; j++)
	{
		for (flag = 0x80, i = 0; i < 8; i++, flag >>= 1)
		{
			if (flag & zimo[j])
			{
				DrawOnePixel(pTmpRgb, xpos+i, ypos+j, TmpFR, TmpFG, TmpFB);
			}
			else 
			{
				DrawOnePixel(pTmpRgb, xpos+i, ypos+j, TmpBR, TmpBG, TmpBB);
			}
		}
	}

	return 0;
}


/* 绘制字符串 */
int DrawString(Rgb_t *pTmpRgb, int xpos, int ypos, char *pstr, unsigned char TmpFR, unsigned char TmpFG, unsigned char TmpFB, unsigned char TmpBR, unsigned char TmpBG, unsigned char TmpBB)
{
	int i = 0;

	while (*pstr != '\0')
	{
		DrawOneAscii(pTmpRgb, xpos + i * 10, ypos, *pstr, TmpFR, TmpFG, TmpFB, TmpBR, TmpBG, TmpBB);
		i++;
		pstr++;
	}

	return 0;
}

/* 绘制汉字 */
int DrawOneHanZi(Rgb_t *pTmpRgb, int xpos, int ypos, char *pstr, unsigned char TmpFR, unsigned char TmpFG, unsigned char TmpFB, unsigned char TmpBR, unsigned char TmpBG, unsigned char TmpBB)
{
	unsigned char zimo[32] = {0};
	int i = 0;
	int j = 0;
	unsigned char flag = 0;
	int len = sizeof(gHanziList) / sizeof(gHanziList[0]);

	for (i = 0; i < len; i++)
	{
		if (!strcmp(gHanziList[i].str, pstr))
		{
			memcpy(zimo, gHanziList[i].zimo, 32);
			break;
		}
	}

	for (j = 0; j < 16; j++)
	{
		for (flag = 0x80, i = 0; i < 8; i++, flag >>= 1)
		{
			if (flag & zimo[2*j])
			{
				DrawOnePixel(pTmpRgb, xpos+i, ypos+j, TmpFR, TmpFG, TmpFB);	
			}
			else 
			{
				DrawOnePixel(pTmpRgb, xpos+i, ypos+j, TmpBR, TmpBG, TmpBB);	
			}
		}

		for (flag = 0x80, i = 8; i < 16; i++, flag >>= 1)
		{
			if (flag & zimo[2*j+1])
			{
				DrawOnePixel(pTmpRgb, xpos+i, ypos+j, TmpFR, TmpFG, TmpFB);	
			}
			else 
			{
				DrawOnePixel(pTmpRgb, xpos+i, ypos+j, TmpBR, TmpBG, TmpBB);	
			}
		}
	}

	return 0;
}

/* 绘制汉字字符串 */
int DrawHanZiString(Rgb_t *pTmpRgb, int xpos, int ypos, char *pstr, unsigned char TmpFR, unsigned char TmpFG, unsigned char TmpFB, unsigned char TmpBR, unsigned char TmpBG, unsigned char TmpBB)
{
	char *p = pstr;
	unsigned char hanzi[4] = {0};
	int i = 0;

	while (*p != '\0')
	{
		memcpy(hanzi, p, 3);

		DrawOneHanZi(pTmpRgb, xpos + i * 18, ypos, hanzi, TmpFR, TmpFG, TmpFB, TmpBR, TmpBG, TmpBB);
		i++;
		
		p += 3;
	}

	return 0;
}

/* 显示bmp图片 */
int DrawBmp(Rgb_t *pTmpRgb, int xpos, int ypos, char *pBmpName)
{
	int fd = 0;
	int width = 0;
	int height = 0;
	int i = 0;
	int j = 0;
	unsigned char col[3] = {0};

	fd = open(pBmpName, O_RDONLY);
	if (-1 == fd)
	{
		return -1;
	}

	lseek(fd, 18, SEEK_SET);
	read(fd, &width, 4);
	read(fd, &height, 4);
		
	lseek(fd, 54, SEEK_SET);

	for (j = height-1; j >= 0; j--)
	{
		for (i = 0; i < width; i++)
		{
			read(fd, col, sizeof(col));
			DrawOnePixel(pTmpRgb, i + xpos, j + ypos, col[2], col[1], col[0]);
		}
		
		if (width * 3 % 4 != 0)
		{
			read(fd, col, (4 - width * 3 % 4));
		}
	}

	close(fd);

	return 0;
}

/* 绘制一条斜线 */
int DrawLine(Rgb_t *pFb, int x0, int y0, int x1, int y1, unsigned char TmpR, unsigned char TmpG, unsigned char TmpB)
{
	int TmpX = 0;
	int TmpY = 0;
	double k = 0;
	int i = 0;

	if (y0 == y1)
	{
		if (x0 < x1)
		{
			DrawHorLine(pFb, x0, y0, x1-x0, TmpR, TmpG, TmpB);
			return 0;
		}
		else if (x0 > x1)
		{
			DrawHorLine(pFb, x1, y1, x0 - x1, TmpR, TmpG, TmpB);
			return 0;
		}
	}

	k = (double)(y1 - y0) / (double)(x1 - x0);
	if (k > 0 && k <= 1 || k < 0 && k >=-1)
	{
		if (x0 < x1)
		{
			for (i = x0; i <= x1; i++)
			{
				DrawOnePixel(pFb, i, y0 + k * (i-x0), TmpR, TmpG, TmpB);
			}
		}
		else if (x0 > x1)
		{
			for (i = x1; i <= x0; i++)
			{
				DrawOnePixel(pFb, i, y1 + k * (i - x1), TmpR, TmpG, TmpB);
			}
		}		
	}
	else if (k > 1 || k < -1)
	{
		if (y0 < y1)
		{
			for (i = y0; i <= y1; i++)
			{
				DrawOnePixel(pFb, x0 + ((i-y0) / k), i, TmpR, TmpG, TmpB);
			}
		}
		else if (y0 > y1)
		{
			for (i = y1; i <= y0; i++)
			{
				DrawOnePixel(pFb, x1 + ((i-y1) / k), i, TmpR, TmpG, TmpB);
			}
		}
	}

#if 0
	if (x0 == x1)
	{
		if (y0 < y1)
		{
			DrawVerLine(pFb, x0, y0, y1-y0, TmpR, TmpG, TmpB);
			return 0;
		}
		else if (y0 > y1)
		{
			DrawVerLine(pFb, x1, y1, y0 - y1, TmpR, TmpG, TmpB);
			return 0;
		}
	}

	if (x0 < x1)
	{
		k = (double)(y1 - y0) / (double)(x1 - x0);
		for (i = x0; i <= x1; i++)
		{
			DrawOnePixel(pFb, i, y0 + k * (i-x0), TmpR, TmpG, TmpB);
		}
	}
	else if (x0 > x1)
	{
		k = (double)(y0 - y1) / (double)(x0 - x1);
		for (i = x1; i <= x0; i++)
		{
			DrawOnePixel(pFb, i, y1 + k * (i - x1), TmpR, TmpG, TmpB);
		}
	}
#endif

	return 0;
}

/* 读取JPEG图片到缓存中 */
int ReadJPEGFile(const char *jpegData, char *rgbdata, int size)
{
	struct jpeg_error_mgr jerr;
	struct jpeg_decompress_struct cinfo;

	cinfo.err = jpeg_std_error(&jerr);
	
	//1创建解码对象并且初始化
	jpeg_create_decompress(&cinfo);
	
	//2.装备解码的数据
	//jpeg_stdio_src(&cinfo, infile);
	
	jpeg_mem_src(&cinfo,(unsigned char*)jpegData, size);
	
	//3.获取jpeg图片文件的参数
	(void) jpeg_read_header(&cinfo, TRUE);
	
	/* Step 4: set parameters for decompression */
	//5.开始解码
	(void) jpeg_start_decompress(&cinfo);
	
	//6.申请存储一行数据的内存空间
	int row_stride = cinfo.output_width * cinfo.output_components;
	unsigned char *buffer = malloc(row_stride);
	int i = 0;
	while (cinfo.output_scanline < cinfo.output_height) {
		(void) jpeg_read_scanlines(&cinfo, &buffer, 1); 
		memcpy(rgbdata + i * cinfo.output_width * 3, buffer, row_stride);
		i++;
	}

	//7.解码完成
	(void) jpeg_finish_decompress(&cinfo);
	
	//8.释放解码对象
	jpeg_destroy_decompress(&cinfo);
	
	return 1;
}

/* 将内存中的RGB信息显示在屏幕上 */
int ShowRgbInfo(Rgb_t *pTmpRgb, unsigned char *rgbdata, int xpos, int ypos, int width, int height)
{
	unsigned char Col[3] = {0};
	unsigned char (*pCol)[3] = NULL;

	pCol = (unsigned char(*)[3])rgbdata;
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			DrawOnePixel(pTmpRgb, xpos + i, ypos + j, pCol[0][0], pCol[0][1], pCol[0][1]);
			pCol++;
		}
	}

	return 0;
}

/* ************************************************************************
 *
 * 视频显示 
 *
 * 参数:
 *		pTmpRgb: FrameBuffInit获得的句柄
 *		VideoDevName: video设备文件,例如:/dev/video0
 *		Width:  设置video采集图像的宽
 *		Height: 设置Video采集图像的高
 *				例如: 320*240、640*360
 *		xpos: 显示图像的x坐标
 *		ypos: 显示图像的y坐标 
 * 注意事项:
 *		1.循环显示，函数会阻塞
 * ************************************************************************/
int VideoShow(Rgb_t *pTmpRgb, const char *VideoDevName, int Width, int Height, int xpos, int ypos)
{
	//1.打开设备
	int fd = open(VideoDevName, O_RDWR);
	if(fd < 0)
	{
		perror("open is error\n");
		return -1;
	}

	//3.设置采集格式
	struct v4l2_format vfmt;
	vfmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;//摄像头采集
	vfmt.fmt.pix.width = Width;//设置宽（不能任意）
	vfmt.fmt.pix.height = Height;//设置高
	vfmt.fmt.pix.pixelformat = V4L2_PIX_FMT_MJPEG;//设置视频采集格式
	int ret = ioctl(fd, VIDIOC_S_FMT, &vfmt);//set
	if(ret < 0)
	{
		perror("VIDIOC_S_FMT is error\n");
		return -1;
	}

	//4.申请内核空间
	struct v4l2_requestbuffers reqbuffer;
	reqbuffer.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	reqbuffer.count = 4; //申请4个缓冲区
	reqbuffer.memory = V4L2_MEMORY_MMAP ;//映射方式
	ret  = ioctl(fd, VIDIOC_REQBUFS, &reqbuffer);
	if(ret < 0)
	{
		perror("VIDIOC_REQBUFS is error\n");
		return -1;
	}

	//5.映射
	unsigned char *mptr[4];//保存映射后用户空间的首地址
    unsigned int  size[4];
	struct v4l2_buffer mapbuffer;

	//初始化type, index
	mapbuffer.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	for(int i = 0; i < 4; i++)
	{
		mapbuffer.index = i;
		ret = ioctl(fd, VIDIOC_QUERYBUF, &mapbuffer);//从内核空间中查询一个空间做映射
		if(ret < 0)
		{
			perror("VIDIOC_QUERYBUF is error\n");
			return -1;
		}
		mptr[i] = (unsigned char *)mmap(NULL, mapbuffer.length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, mapbuffer.m.offset);
        size[i] = mapbuffer.length;

		//通知使用完毕--‘放回去’
		ret  = ioctl(fd, VIDIOC_QBUF, &mapbuffer);
		if(ret < 0)
		{
			perror("VIDIOC_QBUF is error\n");
			return -1;
		}
	}
	
	//6.start 
	int type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	ret = ioctl(fd, VIDIOC_STREAMON, &type);
	if(ret < 0)
	{
		perror("VIDIOC_STREAMON is error\n");
		return -1;
	}

	//申请空间存储解码数据 
	unsigned char *prgbdata = NULL;
	prgbdata = malloc(Width * Height * 3);
	if (NULL == prgbdata)
	{
		return -1;
	}

	while(1)
	{
		//7.从队列中提出一帧数据 
		struct v4l2_buffer  readbuffer;
		readbuffer.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		ret = ioctl(fd, VIDIOC_DQBUF, &readbuffer);
		if(ret < 0)
		{
			perror("VIDIOC_DQBUF is error\n");
			return -1;
		}

		//显示在LCD上
		ReadJPEGFile(mptr[readbuffer.index], prgbdata, readbuffer.length);
		
		//保存图片暂时不需要使用
		int fjpg = 0;
		fjpg = open("tmp.jpg", O_WRONLY | O_TRUNC | O_CREAT, 0664);
		if (-1 == fjpg)
		{
			perror("fail to open");
			return -1;
		}
		write(fjpg, mptr[readbuffer.index], readbuffer.length);
		close(fjpg);

		ShowRgbInfo(pTmpRgb, prgbdata, xpos, ypos, Width, Height);
		
		//通知内核已经使用完毕
		ret = ioctl(fd, VIDIOC_QBUF, &readbuffer);
		if(ret < 0)
		{
			perror("VIDIOC_QBUF is error\n");
			return -1;
		}
	}

	ret = ioctl(fd, VIDIOC_STREAMOFF, &type);
    
    for(int i = 0; i < 4; i++)
	{
		munmap(mptr[i], size[i]);
	}

	free(prgbdata);

	close(fd);

	return 0;
}

/* 绘制鼠标 */
int DrawMouse(Rgb_t *pTmpRgb, int x, int y)
{
	static int IsFirst = 1;			/* 是否第一次绘制 */
	static int Oldx = 0;
	static int Oldy = 0;
	static int Newx = 0;
	static int Newy = 0;
	static Rgb888_t Old[20*20];
	static Rgb888_t New[20*20];
	
	if (!IsNewPosition(Oldx, Oldy, x, y, 20, 20))
	{
		return 0;
	}

	/* 保存目标位置的图像信息 */
	Newx = x;
	Newy = y;
	SavePosRgbInfo(pTmpRgb, x, y, 20, 20, New);

	/* 将鼠标绘制在目标位置 */
	FillDict(pTmpRgb, x, y, 20, 20, 255, 0, 0);
	
	if (!IsFirst)
	{
		/* 还原鼠标原来位置的图像信息 */
		RecoveryRgbInfo(pTmpRgb, Oldx, Oldy, 20, 20, Old);
	}
	else
	{
		IsFirst = 0;
	}

	/* 更新当前鼠标位置的信息 */
	Oldx = Newx;
	Oldy = Newy;
	memcpy(Old, New, sizeof(New));

	return 0;
}

/* ***********************************************************************************
 *
 * 将某个图像位置信息RGB存放到数组中 
 *
 * 参数:
 *	pTmpRgb:显存句柄
 *	x:保存图像的x坐标
 *	y:保存推向的y坐标
 *	width:保存图像的宽度
 *	height:保存图像的高度
 *	parray:存放RGB信息的空间首地址
 * ***********************************************************************************/
int SavePosRgbInfo(Rgb_t *pTmpRgb, int x, int y, int width, int height, Rgb888_t *parray)
{
	int j = 0;
	Rgb888_t *pTmp = NULL;

	pTmp = pTmpRgb->pRgb888;

	for (j = 0; j < height; j++)
	{
		memcpy(parray + j * width, pTmp + (((y+j) * pTmpRgb->vinfo.xres_virtual)+x), width * sizeof(Rgb888_t));
	}

	return 0;
}

/* ***********************************************************************************
 *
 * 将某个图像信息还原回显存空间中
 *
 * 参数:
 *	pTmpRgb:显存句柄
 *	x:保存图像的x坐标
 *	y:保存推向的y坐标
 *	width:保存图像的宽度
 *	height:保存图像的高度
 *	parray:存放RGB信息的空间首地址
 * ***********************************************************************************/
int RecoveryRgbInfo(Rgb_t *pTmpRgb, int x, int y, int width, int height, Rgb888_t *parray)
{
	int j = 0;
	Rgb888_t *pTmp = NULL;

	pTmp = pTmpRgb->pRgb888;

	for (j = 0; j < height; j++)
	{
		memcpy(pTmp + (((y+j) * pTmpRgb->vinfo.xres_virtual)+x), parray + j * width, width * sizeof(Rgb888_t));
	}

	return 0;
}
