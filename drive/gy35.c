/**
 * filename: uart.c
 * author: Suzkfly
 * date: 2021-01-16
 * platform: Ubuntu
 * 将USB转串口连接至Ubuntu中，运行程序，能打印串口接收到的数据，也能从终端中获取
 * 数据发送出去。
 * 如果不能成功打开设备，使用则ls /dev/ttyUSB0命令看设备是否存在，若存在，则使用
 * sudo chmod 666 /dev/ttyUSB0 修改文件权限后重新运行程序。
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

/**
 * \brief define
 * @{
 */
#define UART_DEV_PATH   "/dev/ttySAC2"  /**\brief< 定义打开的串口设备路径 */

/**
 * @}
 */

/**
 * \brief 打开串口设备
 *
 * \param[in] p_path：设备路径
 *
 * \retval 成功返回文件描述符，失败返回-1
 */
int uart_open(const char *p_path)
{
    /* O_NOCTTY：阻止操作系统将打开的文件指定为进程的控制终端,如果没有指定这个标
                 志，那么任何一个输入都将会影响用户的进程。 */
    /* O_NONBLOCK：使I/O变成非阻塞模式，调用read如果没有接收到数据则立马返回-1，
            并且设置errno为EAGAIN。*/
    /* O_NDELAY： 与O_NONBLOCK完全相同 */
    return open(p_path, O_RDWR | O_NOCTTY);
}

/**
 * \brief 测试函数，打印struct termios各成员值
 */
static void __print_termios(struct termios *p_termios)
{
    printf("c_iflag = %#08x\n", p_termios->c_iflag);
    printf("c_oflag = %#08x\n", p_termios->c_oflag);
    printf("c_cflag = %#08x\n", p_termios->c_cflag);
    printf("c_lflag = %#08x\n\n", p_termios->c_lflag);
}

/**
 * \brief 设置串口属性
 *
 * \param[in] fd：打开的串口设备的文件描述符
 * \param[in] baudrate：波特率
 *            #{0, 50, 75, 110, 134, 150, 200, 300, 600, 1200, 1800,
 *              2400, 4800, 9600, 19200, 38400, 57600, 115200, 230400}
 * \param[in] bits：数据位
 *            #{5, 6, 7, 8}
 * \param[in] parity：校验
 *            #'n'/'N'：无校验
 *            #'o'/'O'：奇校验
 *            #'e','E'：偶校验
 * \param[in] stop：停止位
 *            #1：1个停止位
 *            #2：2个停止位
 * \param[in] flow：流控
 *            #'n'/'N'：不使用流控
 *            #'h'/'H'：使用硬件流控
 *            #'s'/'S'：使用软件流控
 *
 * \retval 成功返回0，失败返回-1，并打印失败原因
 *
 * \note 虽然波特率设置支持这么多值，但并不代表输入表中支持的值波特率就
 *       一定能设置成功。
 */
int uart_set(int fd, int baudrate, int bits, char parity, int stop, char flow)
{
    struct termios termios_uart;
    int ret = 0;
    speed_t uart_speed = 0;

    /* 获取串口属性 */
    memset(&termios_uart, 0, sizeof(termios_uart));
    ret = tcgetattr(fd, &termios_uart);
    if (ret == -1) {
        printf("tcgetattr failed\n");
        return -1;
    }

    //__print_termios(&termios_uart);

    /* 设置波特率 */
    switch (baudrate) {
        case 0:      uart_speed = B0;      break;
        case 50:     uart_speed = B50;     break;
        case 75:     uart_speed = B75;     break;
        case 110:    uart_speed = B110;    break;
        case 134:    uart_speed = B134;    break;
        case 150:    uart_speed = B150;    break;
        case 200:    uart_speed = B200;    break;
        case 300:    uart_speed = B300;    break;
        case 600:    uart_speed = B600;    break;
        case 1200:   uart_speed = B1200;   break;
        case 1800:   uart_speed = B1800;   break;
        case 2400:   uart_speed = B2400;   break;
        case 4800:   uart_speed = B4800;   break;
        case 9600:   uart_speed = B9600;   break;
        case 19200:  uart_speed = B19200;  break;
        case 38400:  uart_speed = B38400;  break;
        case 57600:  uart_speed = B57600;  break;
        case 115200: uart_speed = B115200; break;
        case 230400: uart_speed = B230400; break;
        default: printf("Baud rate not supported\n"); return -1;
    }
    cfsetspeed(&termios_uart, uart_speed);

    /* 设置数据位 */
    switch (bits) {
        case 5:     /* 数据位5 */
            termios_uart.c_cflag &= ~CSIZE;
            termios_uart.c_cflag |= CS5;
        break;

        case 6:     /* 数据位6 */
            termios_uart.c_cflag &= ~CSIZE;
            termios_uart.c_cflag |= CS6;
        break;

        case 7:     /* 数据位7 */
            termios_uart.c_cflag &= ~CSIZE;
            termios_uart.c_cflag |= CS7;
        break;

        case 8:     /* 数据位8 */
            termios_uart.c_cflag &= ~CSIZE;
            termios_uart.c_cflag |= CS8;
        break;

        default:
            printf("Data bits not supported\n");
            return -1;
    }

    /* 设置校验位 */
    switch (parity) {
        case 'n':   /* 无校验 */
        case 'N':
            termios_uart.c_cflag &= ~PARENB;
            termios_uart.c_iflag &= ~INPCK;        /* 禁能输入奇偶校验 */
        break;

        case 'o':   /* 奇校验 */
        case 'O':
            termios_uart.c_cflag |= PARENB;
            termios_uart.c_cflag |= PARODD;
            termios_uart.c_iflag |= INPCK;        /* 使能输入奇偶校验 */
            termios_uart.c_iflag |= ISTRIP;        /* 除去第八个位（奇偶校验位） */
        break;

        case 'e':   /* 偶校验 */
        case 'E':
            termios_uart.c_cflag |= PARENB;
            termios_uart.c_cflag &= ~PARODD;
            termios_uart.c_iflag |= INPCK;        /* 使能输入奇偶校验 */
            termios_uart.c_iflag |= ISTRIP;        /* 除去第八个位（奇偶校验位） */
        break;

        default:
            printf("Parity not supported\n");
            return -1;
    }

    /* 设置停止位 */
    switch (stop) {
        case 1: termios_uart.c_cflag &= ~CSTOPB; break; /* 1个停止位 */
        case 2: termios_uart.c_cflag |= CSTOPB;  break; /* 2个停止位 */
        default: printf("Stop bits not supported\n");
    }

    /* 设置流控 */
    switch (flow) {
        case 'n':
        case 'N':   /* 无流控 */
            termios_uart.c_cflag &= ~CRTSCTS;
            termios_uart.c_iflag &= ~(IXON | IXOFF | IXANY);
        break;

        case 'h':
        case 'H':   /* 硬件流控 */
            termios_uart.c_cflag |= CRTSCTS;
            termios_uart.c_iflag &= ~(IXON | IXOFF | IXANY);
        break;

        case 's':
        case 'S':   /* 软件流控 */
            termios_uart.c_cflag &= ~CRTSCTS;
            termios_uart.c_iflag |= (IXON | IXOFF | IXANY);
        break;

        default:
            printf("Flow control parameter error\n");
            return -1;
    }

    /* 其他设置 */
    termios_uart.c_cflag |= CLOCAL;    /* 忽略modem（调制解调器）控制线 */
    termios_uart.c_cflag |= CREAD;    /* 使能接收 */

    /* 禁能执行定义（implementation-defined）输出处理，意思就是输出的某些特殊数
       据会作特殊处理，如果禁能的话那么就按原始数据输出 */
    termios_uart.c_oflag &= ~OPOST;

    /**
     *  设置本地模式位原始模式
     *  ICANON：规范输入模式，如果设置了那么退格等特殊字符会产生实际动作
     *  ECHO：则将输入字符回送到终端设备
     *  ECHOE：如果ICANON也设置了，那么收到ERASE字符后会从显示字符中擦除一个字符
     *         通俗点理解就是收到退格键后显示内容会往回删一个字符
     *  ISIG：使终端产生的信号起作用。（比如按ctrl+c可以使程序退出）
     */
    termios_uart.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

    /**
     * 设置等待时间和最小接收字符
     * 这两个值只有在阻塞模式下有意义，也就是说open的时候不能传入O_NONBLOCK，
     * 如果经过了c_cc[VTIME]这么长时间，缓冲区内有数据，但是还没达到c_cc[VMIN]个
     * 数据，read也会返回。而如果当缓冲区内有了c_cc[VMIN]个数据时，无论等待时间
     * 是否到了c_cc[VTIME]，read都会返回，但返回值可能比c_cc[VMIN]还大。如果将
     * c_cc[VMIN]的值设置为0，那么当经过c_cc[VTIME]时间后read也会返回，返回值
     * 为0。如果将c_cc[VTIME]和c_cc[VMIN]都设置为0，那么程序运行的效果与设置
     * O_NONBLOCK类似，不同的是如果设置了O_NONBLOCK，那么在没有数据时read返回-1，
     * 而如果没有设置O_NONBLOCK，那么在没有数据时read返回的是0。
     */
    termios_uart.c_cc[VTIME] = 1;   /* 设置等待时间，单位1/10秒 */
    termios_uart.c_cc[VMIN]  = 1;    /* 最少读取一个字符 */

    tcflush(fd, TCIFLUSH);          /* 清空读缓冲区 */

    /* 写入配置 */
    ret = tcsetattr(fd, TCSANOW, &termios_uart);
    if (ret == -1) {
        printf("tcsetattr failed\n");
    }

    return ret;
}


int unpackage(unsigned char * data, int len)
{
	unsigned char sum = 0;
	int i = 0;
	for(i = 0; i < len - 1; i++)
	{
		sum += data[i];
	}

	if(sum == data[i])
		return 0;
	
	return -1;
}

int main(int argc, const char *argv[])
{
    int fd = 0;
    int ret = 0;
    int len = 0;
    int i = 0;

    /* 打开串口设备 */
    fd = uart_open("/dev/ttySAC1");
    if (fd < 0) {
        printf("open %s failed\n", UART_DEV_PATH);
        return 0;
    }

    ret = uart_set(fd, 9600, 8, 'n', 1, 'n');
    if (ret == -1) {
        return 0;
    }

    unsigned char buf[1024] = { 0 };
	int read_num = 0;
	while(1)
	{
		int num = read(fd, &buf[read_num], sizeof(buf));
		read_num += num;
		printf("num = %d read_num = %d\n", num, read_num);
	
		int p = 0;
		while(read_num >= 8)
		{
			if(buf[p] == 0x5A && buf[p+1] == 0x5A)
			{
				int len = buf[p+3] + 5;
				int ret = unpackage(&buf[p], len);	
				if(ret < 0)
				{
					printf("is not a complete package data!");
					p++;
				}
				else
				{
					unsigned short dis = buf[p+4] << 8 | buf[5];
					printf("dis = %d mm\n", dis);
					read_num -= (len + p);
					memcpy(&buf[0], &buf[p + len], read_num);
					memset(&buf[p + read_num], 0, sizeof(buf) - read_num);
					p = 0;
				}
			}
			else
			{
				if(p > 13)
				{
					read_num -= (p);
					memcpy(&buf[0], &buf[p], read_num);
					memset(&buf[p + read_num], 0, sizeof(buf) - read_num);
					p = 0;
				}
				else
					p++;
			}
		}

		for(i = 0; i < read_num; i++)
		{
			printf("%02x  ", buf[i]);
		}
		printf("\n");
	}
	
    return 0;
}

