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

// dev_num
// file_operations
//register
#define MAJOR_NUM 251
#define MINOR_NUM  0
#define DEV_NAME "adc"
#define ADCCON 0x58000000
#define ADCDAT0 0x5800000C
#define CLKCON 0x4C00000C
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
	int ret = 0;
	init_adc();
	ret = request_irq(IRQ_ADC, irq_handler, IRQF_DISABLED, "adc_irq", NULL);
	if(ret < 0)
		goto err;

	printk("kernel open ...\n");
	return 0;

err:
	disable_irq(IRQ_ADC);
	free_irq(IRQ_ADC, NULL);
	printk("kernel request_irq failed ...\n");
	return ret;

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
	disable_irq(IRQ_ADC);
	free_irq(IRQ_ADC, NULL);
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

static __init int adc_init(void)
{
	int ret = misc_register(&misc_dev);	
	if(ret < 0)
		goto err;

	adccon = ioremap(ADCCON, 4);
	adcdat0 = ioremap(ADCDAT0, 4);
	clkcon = ioremap(CLKCON, 4);

	*clkcon |= (1 << 15);
	printk("CLKCON = %lX\n", *clkcon);

	init_waitqueue_head(&wq);

	printk("adc_init    ######################################\n");
	return 0;

err:
	misc_deregister(&misc_dev);
	printk("kernel adc misc_register  failed ret = %d\n", ret);
	return ret;
}

static __exit void adc_exit(void)
{
	iounmap(adccon);
	iounmap(adcdat0);
	iounmap(clkcon);
	misc_deregister(&misc_dev);
	printk("adc_exit    #######################################\n");
}

module_init(adc_init);
module_exit(adc_exit);
MODULE_LICENSE("GPL");
