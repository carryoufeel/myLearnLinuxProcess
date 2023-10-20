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
#define ADCCON 0x58000000
#define ADCDAT0 0x5800000C
#define CLKCON 0x4C00000C
#define ADC_IRQ_NUM IRQ_ADC

static struct resource res[4] = 
{
	[0] = 
	{
		.start = ADCCON,
		.end = ADCCON + 4 - 1,
		.name = "adccon",
		.flags = IORESOURCE_IO 
	},
	[1] = 
	{
		.start = ADCDAT0,
		.end = ADCDAT0 + 4 - 1,
		.name = "adcdat0",
		.flags = IORESOURCE_IO
	},
	[2] = 
	{
		.start = CLKCON,
		.end = CLKCON + 4 - 1,
		.name = "clkcon",
		.flags = IORESOURCE_IO
	},
	[3] = 
	{
		.start = ADC_IRQ_NUM,
		.end = ADC_IRQ_NUM,
		.name = "adc_irq",
		.flags = IORESOURCE_IRQ
	},
};

static void release(struct device * dev){}
static struct platform_device dev = 
{
	.name = DEV_NAME,
	.id = -1,
	.dev = 
	{
		.release = release	
	},
	.num_resources = sizeof(res)/sizeof(res[0]),
	.resource = res 
};

static __init int adc_init(void)
{
	int ret = platform_device_register(&dev);
	if(ret < 0)
		goto err;

	printk("adc platform_device_register  ...\n");
	return 0;

err:
	platform_device_unregister(&dev);
	printk("adc platform_device_register failed\n");
	return ret;
}

static __exit void adc_exit(void)
{
	platform_device_unregister(&dev);
	printk("adc platform_device_unregister ...\n");
}

module_init(adc_init);
module_exit(adc_exit);
MODULE_LICENSE("GPL");
