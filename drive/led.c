#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/types.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <asm/uaccess.h>
#include <asm/io.h>

// dev_num
// file_operations
//register
#define MAJOR_NUM 253
#define MINOR_NUM  0
#define DEV_NAME "led"
#define GPBCON 0x56000010
#define GPBDAT 0x56000014
static volatile unsigned long * gpbcon;
static volatile unsigned long * gpbdat;

static void init_led(void)
{
	*gpbcon &= ~(0x3 << 10);
	*gpbcon |= (0x1 << 10);
	*gpbdat |= (0x1 << 5);
}

static void led_on(void)
{
	*gpbdat &= ~(0x1 << 5);
}

static void led_off(void)
{
	*gpbdat |= (0x1 << 5);
}

static int open(struct inode * node, struct file * file)
{
	init_led();
	printk("kernel open ...\n");
	return 0;
}

static ssize_t read(struct file * file, char __user * buf, size_t len, loff_t * loff)
{
	// copy_to_user();
	printk("kernel read ...\n");
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
	return len_cp;
}

static int close(struct inode * node, struct file * file)
{
	printk("kernel close ...\n");
	return 0;
}

static dev_t dev_num;
static struct cdev dev;
static struct file_operations fops = 
{
	.owner = THIS_MODULE,
	.open = open,
	.read = read,
	.write = write,
	.release = close
};

static __init int led_init(void)
{
	int ret = 0;
	dev_num = MKDEV(MAJOR_NUM, MINOR_NUM);

	cdev_init(&dev, &fops);

	ret = cdev_add(&dev, dev_num, 1);
	if(ret < 0)
		goto err1;
	
	ret = register_chrdev_region(dev_num, 1, DEV_NAME);
	if(ret < 0)
		goto err2;

	gpbcon = ioremap(GPBCON, sizeof(gpbcon));
	gpbdat = ioremap(GPBDAT, sizeof(gpbdat));

	printk("led_init    ######################################\n");
	return 0;

err1:
	cdev_del(&dev);
	printk("kernel led cdev_add  failed ret = %d\n", ret);
	return ret;

err2:
	unregister_chrdev_region(dev_num, 1);
	cdev_del(&dev);
	printk("kernel led register_chrdev_region failed  ret = %d\n", ret);
	return ret;
}

static __exit void led_exit(void)
{
	unregister_chrdev_region(dev_num, 1);
	cdev_del(&dev);
	printk("led_exit    #######################################\n");
}

module_init(led_init);
module_exit(led_exit);
MODULE_LICENSE("GPL");

