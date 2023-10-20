#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/types.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/module.h>
#include <linux/kdev_t.h>

// dev_num
// file_operations
//register
#define MAJOR_NUM 255
#define MINOR_NUM  0
#define DEV_NAME "hello"

static int open(struct inode * node, struct file * file)
{
	printk("kernel open ...\n");
	return 0;
}

static ssize_t read(struct file * file, char __user * buf, size_t len, loff_t * loff)
{
	printk("kernel read ...\n");
	return 0;
}

static ssize_t write(struct file * file, const char __user * buf, size_t len, loff_t * loff)
{
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

static __init int hello_init(void)
{
	dev_num = MKDEV(MAJOR_NUM, MINOR_NUM);

	cdev_init(&dev, &fops);

	cdev_add(&dev, dev_num, 1);
	
	register_chrdev_region(dev_num, 1, DEV_NAME);

	printk("hello_init    ######################################\n");
	return 0;
}

static __exit void hello_exit(void)
{
	unregister_chrdev_region(dev_num, 1);
	cdev_del(&dev);
	printk("hello_exit    #######################################\n");
}

module_init(hello_init);
module_exit(hello_exit);
