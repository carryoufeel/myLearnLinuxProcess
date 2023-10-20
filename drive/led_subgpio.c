#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/types.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/interrupt.h>
#include <mach/irqs.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include <linux/miscdevice.h>
#include <mach/gpio.h>
#include <mach/gpio-nrs.h>

// dev_num
// file_operations
//register
#define DEV_NAME "led"
#define GPIO_LED  S3C2410_GPB(5) 
#define LED_OFF 1
#define LED_ON  0

static void init_led(void)
{
	gpio_request(GPIO_LED, "gpio_led");
	gpio_direction_output(GPIO_LED, LED_OFF);
}

static void led_on(void)
{
	gpio_set_value(GPIO_LED, LED_ON);
}

static void led_off(void)
{
	gpio_set_value(GPIO_LED, LED_OFF);
}

static void led_deinit(void)
{
	gpio_free(GPIO_LED);
}

static int open(struct inode * node, struct file * file)
{
	init_led();
	printk("kernel open ...\n");
	return 0;
}

static ssize_t read(struct file * file, char __user * buf, size_t len, loff_t * loff)
{
	return 0;
}

static ssize_t write(struct file * file, const char __user * buf, size_t len, loff_t * loff)
{
	//led on  /  off
	char data[100] = {0};
	int len_cp = sizeof(data) < len ? sizeof(data) : len;
	copy_from_user(data, buf, len_cp);
	if(!strcmp(buf, "on"))
	{
		led_on();
	}
	else if(!strcmp(buf, "off"))
	{
		led_off();
	}
	else 
	{
		return -1;	
	}
	
	printk("kernel write ...\n");
	return 0;
}

static int close(struct inode * node, struct file * file)
{
	led_deinit();
	printk("kernel close ...\n");
	return 0;
}

static struct file_operations fops = 
{
	.owner = THIS_MODULE,
	.open = open,
	.read = read,
	.write = write,
	.release = close
};

struct miscdevice misc_dev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = DEV_NAME,
	.fops = &fops
};

static __init int led_init(void)
{
	int ret = misc_register(&misc_dev);	
	if(ret < 0)
		goto err;

	printk("led_init    ######################################\n");
	return 0;

err:
	misc_deregister(&misc_dev);
	printk("kernel led misc_register  failed ret = %d\n", ret);
	return ret;
}

static __exit void led_exit(void)
{
	misc_deregister(&misc_dev);
	printk("led_exit    #######################################\n");
}

module_init(led_init);
module_exit(led_exit);
MODULE_LICENSE("GPL");
