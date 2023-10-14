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
#define DEV_NAME "key"
#define GPGCON 0x56000060
#define GPGDAT 0x56000064
static volatile unsigned long * gpgcon;
static volatile unsigned long * gpgdat;
static void init_key(void)
{
	*gpgcon &= ~(0x3<<0);
	*gpgcon &= ~(0x3 << 6);
	*gpgcon &= ~(0x3 << 10);
	*gpgcon &= ~(0x3 << 12);
	*gpgcon &= ~(0x3 << 14);
	*gpgcon &= ~(0x3 << 22);
}

static unsigned char key_status(void)
{
	if(!(*gpgdat &(1<<0)))
		return 1;
	if(!(*gpgdat &(1<<3)))
		return 2;
	if(!(*gpgdat &(1<<5)))
		return 3;
	if(!(*gpgdat &(1<<6)))
		return 4;
	if(!(*gpgdat &(1<<7)))
		return 5;
	if(!(*gpgdat &(1<<11)))
		return 6;
	return 0;
}
static int open(struct inode * node, struct file * file)
{
	init_key();
	printk("kernel open ...\n");
	return 0;
}

static ssize_t read(struct file * file, char __user * buf, size_t len, loff_t * loff)
{

	unsigned char status =0;
	status=key_status();
	copy_to_user(buf,&status,sizeof(status));
	printk("kernel read\n");
	return 0;
}

static ssize_t write(struct file * file, const char __user * buf, size_t len, loff_t * loff)
{
	//led on  /  off
	printk("kernel write ...\n");
	return 0;
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

static __init int key_init(void)
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
	
		gpgcon = ioremap(GPGCON, sizeof(gpgcon));
		gpgdat = ioremap(GPGDAT, sizeof(gpgdat));
	printk("key_init    ######################################\n");
	return 0;

err1:
	cdev_del(&dev);
	printk("kernel key cdev_add  failed ret = %d\n", ret);
	return ret;

err2:
	unregister_chrdev_region(dev_num, 1);
	cdev_del(&dev);
	printk("kernel key register_chrdev_region failed  ret = %d\n", ret);
	return ret;
}

static __exit void key_exit(void)
{
	unregister_chrdev_region(dev_num, 1);
	cdev_del(&dev);
	printk("key_exit    #######################################\n");
}

module_init(key_init);
module_exit(key_exit);
MODULE_LICENSE("GPL");

