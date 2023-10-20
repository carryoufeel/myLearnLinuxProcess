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
#include <linux/platform_device.h>

// dev_num
// file_operations
//register
#define DEV_NAME "adc"

static volatile unsigned long * adccon;
static volatile unsigned long * adcdat0;
static volatile unsigned long * clkcon;
static wait_queue_head_t wq;
static int condition = 0;

static irqreturn_t irq_handler(int irq_num, void * args)
{
	printk(" kernel irq_handler irq_num = %d\n", irq_num);
	condition = 1;
	wake_up_interruptible(&wq);
	return IRQ_HANDLED;
}

static void init_adc(void)
{
	*adccon = (1 << 14) | (49 << 6);	
}

static int open(struct inode * node, struct file * file)
{
	init_adc();
	printk("kernel open ...\n");

	return 0;
}

static ssize_t read(struct file * file, char __user * buf, size_t len, loff_t * loff)
{
	// start c
	unsigned short value = 0;
	printk("kernel read start ...\n");
	*adccon |= (1 << 0);

	condition = 0;
	wait_event_interruptible(wq, condition);

	value = *adcdat0 & 0x3ff;
	copy_to_user(buf, &value, sizeof(value));
	printk("kernel read end ...\n");

	return sizeof(value);
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

int probe(struct platform_device * pdev)
{
	int ret = misc_register(&misc_dev);	
	if(ret < 0)
		goto err;

	adccon = ioremap(pdev->resource[0].start, pdev->resource[0].end - pdev->resource[0].start + 1);
	adcdat0 = ioremap(pdev->resource[1].start, pdev->resource[1].end - pdev->resource[1].start + 1);
	clkcon = ioremap(pdev->resource[2].start, pdev->resource[2].end - pdev->resource[2].start + 1);

	*clkcon |= (1 << 15);
	printk("CLKCON = %lX\n", *clkcon);

	init_waitqueue_head(&wq);

	ret = request_irq(pdev->resource[3].start, irq_handler, IRQF_DISABLED, "adc_irq", NULL);
	if(ret < 0)
		goto err1;

	printk("kernel adc probe    ######################################\n");
	return 0;

err:
	misc_deregister(&misc_dev);
	printk("kernel probe adc misc_register  failed ret = %d\n", ret);
	return ret;

err1:
	disable_irq(pdev->resource[3].start);
	free_irq(pdev->resource[3].start, NULL);
	misc_deregister(&misc_dev);
	printk("kernel probe request_irq failed ...\n");
	return ret;
}

int remove(struct platform_device * pdev)
{
	disable_irq(pdev->resource[3].start);
	free_irq(pdev->resource[3].start, NULL);
	iounmap(adccon);
	iounmap(adcdat0);
	iounmap(clkcon);
	misc_deregister(&misc_dev);
	printk("adc remove    #######################################\n");

	return 0;
}

static struct platform_driver dri = 
{
	.probe = probe,
	.remove = remove,
	.driver = 
	{
		.name = DEV_NAME	
	}
};

static __init int adc_init(void)
{
	int ret = platform_driver_register(&dri);
	if(ret < 0)
		goto err;

	printk("platform_driver_register ...\n");
	return 0;
		
err:
	platform_driver_unregister(&dri);
	printk("platform_driver_register  failed\n");
	return ret;
}

static __exit void adc_exit(void)
{
	platform_driver_unregister(&dri);
	printk("platform_driver_unregister ...\n");
}

module_init(adc_init);
module_exit(adc_exit);
MODULE_LICENSE("GPL");
