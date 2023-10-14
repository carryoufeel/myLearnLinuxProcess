#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/videodev2.h>
#include <string.h>
#include <sys/mman.h>
#include <jpeglib.h>
#include <linux/fb.h>

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
		memcpy(rgbdata + i * cinfo.image_width * 3, buffer, row_stride );
		i++;
	}

	//7.解码完成
	(void) jpeg_finish_decompress(&cinfo);
	
	//8.释放解码对象
	jpeg_destroy_decompress(&cinfo);
	
	return 1;
}


int lcdfd=0;
unsigned int *lcdptr=NULL;

void FrameBuffShowRgbInfo(unsigned char *rgbdata, int width, int height)
{
	unsigned int *ptr = lcdptr;
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			memcpy(ptr+j, rgbdata + j*3, 3);
		}
		ptr += lcd_w;
		rgbdata += width * 3;
	}
}

int main(void)
{
	lcdfd=open("/dev/fb0",O_RDWR);
	if(lcdfd<0)
	{
		printf("lcd open is error\n");
		return -1;
	}

	struct fb_var_screeninfo info;
	int lret=ioctl(lcdfd,FBIOGET_VSCREENINFO,&info);
	lcd_w=info.xres_virtual;
	lcd_h=info.yres_virtual;

	lcdptr=(unsigned int*)mmap(NULL, lcd_w * lcd_h * 4,PROT_READ|PROT_WRITE,MAP_SHARED,lcdfd,0);

	//1.打开设备
	int fd = open("/dev/video0", O_RDWR);
	if(fd < 0)
	{
		perror("open is error\n");
		return -1;
	}

	//3.设置采集格式
	struct v4l2_format vfmt;
	vfmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;//摄像头采集
	vfmt.fmt.pix.width = 320;//设置宽（不能任意）
	vfmt.fmt.pix.height = 240;//设置高
	vfmt.fmt.pix.pixelformat = V4L2_PIX_FMT_MJPEG;//设置视频采集格式
	int ret = ioctl(fd, VIDIOC_S_FMT, &vfmt);//set
	if(ret < 0)
	{
		perror("VIDIOC_S_FMT is error\n");
	}
    printf("3 is okey\n");

	//4.申请内核空间
	struct v4l2_requestbuffers reqbuffer;
	reqbuffer.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	reqbuffer.count = 4; //申请4个缓冲区
	reqbuffer.memory = V4L2_MEMORY_MMAP ;//映射方式
	ret  = ioctl(fd, VIDIOC_REQBUFS, &reqbuffer);
	if(ret < 0)
	{
		perror("VIDIOC_REQBUFS is error\n");
	}
    printf("4 is okey\n");

	//5.映射
	unsigned char *mptr[4];//保存映射后用户空间的首地址
    unsigned int  size[4];
	struct v4l2_buffer mapbuffer;
	//初始化type, index
	mapbuffer.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	for(int i=0; i<4; i++)
	{
		mapbuffer.index = i;
		ret = ioctl(fd, VIDIOC_QUERYBUF, &mapbuffer);//从内核空间中查询一个空间做映射
		if(ret < 0)
		{
			perror("VIDIOC_QUERYBUF is error\n");
		}
		mptr[i] = (unsigned char *)mmap(NULL, mapbuffer.length, PROT_READ|PROT_WRITE, MAP_SHARED, fd, mapbuffer.m.offset);
        size[i]=mapbuffer.length;

		//通知使用完毕--‘放回去’
		ret  = ioctl(fd, VIDIOC_QBUF, &mapbuffer);
		if(ret < 0)
		{
			perror("VIDIOC_QBUF is error\n");
		}
	}
    printf("5 is okey\n");

	
	//6.start 
	int type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	ret = ioctl(fd, VIDIOC_STREAMON, &type);
	if(ret < 0)
	{
		perror("VIDIOC_STREAMON is error\n");
	}
	printf("6 is okey\n");

	//ding yi yi ge kong jian cun chu jie ma hou de rgb shu ju
	unsigned char rgbdata[640*480*3];
	while(1)
	{
		//7.cong dui lie zhong ti qu yi zhen shu ju
		struct v4l2_buffer  readbuffer;
		readbuffer.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		ret = ioctl(fd, VIDIOC_DQBUF, &readbuffer);
		if(ret < 0)
		{
			perror("VIDIOC_DQBUF is error\n");
		}
		printf("777\n");
		//xian shi zai lcd shang
		read_JPEG_file (mptr[readbuffer.index], rgbdata, readbuffer.length);
		printf("1212121212\n");
		lcd_show_rgb(rgbdata,640,480);
		printf("7 is okey\n");

		//通知内核已经使用完毕
		ret = ioctl(fd, VIDIOC_QBUF, &mapbuffer);
		if(ret < 0)
		{
			perror("VIDIOC_QBUF is error\n");
		}
		printf("8 is okey\n");
	}

	//end
	ret = ioctl(fd, VIDIOC_STREAMOFF, &type);
	printf("end is okey\n");
    
    for(int i=0; i<4; i++)
	{
		munmap(mptr[i], size[i]);
	}
	printf("munmap is okey\n");

	//9.关闭设备
	close(fd);
	return 0;
}

