#include <linux/module.h>
#include <linux/poll.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/miscdevice.h>
#include <linux/kernel.h>
#include <linux/major.h>
#include <linux/mutex.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/stat.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/tty.h>
#include <linux/kmod.h>
#include <linux/gfp.h>
#include <linux/platform_device.h>
#include <linux/of_gpio.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/slab.h>
#include <linux/fcntl.h>
#include <linux/timer.h>
#include <linux/workqueue.h>
#include <asm/current.h>
#include <linux/delay.h>
#include <linux/ktime.h>
#include <linux/miscdevice.h>
#include <linux/sched.h>

#define DHT11_PIN S3C2410_GPF(0)
#define DEV_NAME "dht11"

static void dht11_reset(void)
{
	gpio_direction_output(DHT11_PIN, 1);
}

static void dht11_start(void)
{
	mdelay(30);
	gpio_set_value(DHT11_PIN, 0);
	mdelay(20);
	gpio_set_value(DHT11_PIN, 1);
	udelay(30);	
	gpio_direction_input(DHT11_PIN);	
	udelay(2);	
}

static int dht11_wait_for_ready(void)
{
	
	int timeout_us = 200;
	/*等待低电平*/
	while(gpio_get_value(DHT11_PIN)&& --timeout_us)
	{
		udelay(1);
	}
	if(!timeout_us)
	{
		printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
		return -1;
	}

	/*现在是低电平*/
	/*等待高电平*/
	timeout_us = 200;
	while(!gpio_get_value(DHT11_PIN)&& --timeout_us)
	{
		udelay(1);
	}
	if(!timeout_us)
	{
		printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
		return -1;
	}

	/*现在是高电平*/
	
	/*等待低电平*/
	
	timeout_us = 200;
	while(gpio_get_value(DHT11_PIN)&& --timeout_us)
	{
		udelay(1);
	}
	if(!timeout_us)
	{
		printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
		return -1;
	}
	return 0;
}

static int dht11_read_byte(unsigned char *buf)
{
	int i;
	int us;
	unsigned char data=0;	
	int timeout_us = 200;
	for(i=0;i<8;i++)
	{
		/*现在是低电平*/
		/*等待高电平*/
		timeout_us = 200;
		while(!gpio_get_value(DHT11_PIN)&& --timeout_us)
		{
			udelay(1);
		}
		if(!timeout_us)
		{
			return -1;
		}

		/* 现在是高电平 */
		/* 等待低电平,累加高电平的时间 */
		timeout_us = 20000000;
		us = 0;
		udelay(40);

		if (gpio_get_value(DHT11_PIN))/*如果得到高电平*/
		{
			/* get bit 1 */
			data = (data << 1) | 1;

			/* 当前位的高电平未结束, 等待 */
			timeout_us = 400;
			us = 0;
			while (gpio_get_value(DHT11_PIN) && --timeout_us)
			{
				udelay(1);
				us++;
			}
			if (!timeout_us)
			{
				printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
				return -1;
			}
			
		}
		else
		{
			/*get bit 0*/
			data = (data<<1)|0;
		}
	}
	*buf = data;
	return 0;
}

/* 实现对应的open/read/write等函数，填入file_operations结构体                   */
static ssize_t dht11_drv_read (struct file *file, char __user *buf, size_t size, loff_t *offset)
{
	unsigned long flags;
	int i;
	unsigned char data[5];

	local_irq_save(flags);	  // 关中断

	/*1.发送高脉冲，启动DHT11*/
	dht11_reset();
	dht11_start();

	/*2.等待DHT11就绪*/
	if(dht11_wait_for_ready())/*设置超时时间等待DHT11*/
	{
		local_irq_restore(flags); // 恢复中断
		printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
		return -EAGAIN;
	}
	/*3.读5字节数据*/
	for(i = 0;i<5;i++)
	{
		if(dht11_read_byte(&data[i]))
		{
			local_irq_restore(flags); // 恢复中断
			return -EAGAIN;
		}
	}

	dht11_reset();
	local_irq_restore(flags); // 恢复中断

	/*4.根据校验码验证数据*/
	if(data[4]!=(data[0]+data[1]+data[2]+data[3]))
		return -1;

	/*5.返回数据到应用空间*/
	/*data[0]/data[1]:湿度*/
	/*data[2]/data[3]:温度*/

	copy_to_user(buf, data, 4);
	return 4;
}

static int dht11_open(struct inode * inode, struct file * file)
{
	int ret = gpio_request(DHT11_PIN, "dht11");
	if(ret < 0)
	{
		printk("request gpio err\n");
		gpio_free(DHT11_PIN);
		return -1;
	}

	gpio_direction_output(DHT11_PIN, 1);
	printk("dht11_open ...\n");
	return 0;
}

static int dht11_close(struct inode * inode, struct file * file)
{
	gpio_free(DHT11_PIN);
	printk("dht11 close ...\n");
	return 0;
}

static struct file_operations dht11_fops = {
	.owner	 = THIS_MODULE,
	.open = dht11_open,
	.read    = dht11_drv_read,
	.release = dht11_close,
};

static struct miscdevice misc_led = 
{
	.minor = MISC_DYNAMIC_MINOR,
	.name = DEV_NAME,
	.fops = &dht11_fops
};

static int __init dht11_init(void)
{
	int ret = misc_register(&misc_led);	
	if(ret != 0)
	{
		misc_deregister(&misc_led);
		return -1;
	}

	printk("dht11_init ...ret = %d\n", ret);
	return ret;
}

static void __exit dht11_exit(void)
{
	misc_deregister(&misc_led);
	printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
}

module_init(dht11_init);
module_exit(dht11_exit);
MODULE_LICENSE("GPL");
