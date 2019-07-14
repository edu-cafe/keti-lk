#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#include <linux/fs.h>
#include <linux/uaccess.h>		//copy_from_user(). copy_to_user()
#include <linux/slab.h>			//kmalloc
#include <linux/cdev.h>			//struct cdev, ..
#include <linux/device.h>		//struct class,...
#include <linux/io.h>			//ioremap(), iounmap(), ..

#ifdef PI1
#define	BCM_IO_BASE	0x20000000
#else
#define	BCM_IO_BASE	0x3F000000
#endif
#define	GPIO_BASE	(BCM_IO_BASE + 0x200000)
#define	GPIO_SIZE	(256)


//GPFSEL0~5 : 0x00~0x14 ManP.90
#define	GPIO_IN(g)		( *(gpio+((g)/10)) &= ~(7 << (((g)%10)*3)) )
#define	GPIO_OUT(g)		( *(gpio+((g)/10)) |= (1 << (((g)%10)*3)) )

//GPSET0 : 0x1C(28)
#define	GPIO_SET(g)		( *(gpio+7) = 1<<g )

//GPCLR0 : 0x28(40)
#define	GPIO_CLR(g)		( *(gpio+10) = 1<<g )

//GPLEV0 : 0x34(52)
#define	GPIO_GET(g)		( *(gpio+13) & (1<<g) )

#define	GPIO_LED	18

volatile unsigned int *gpio;
volatile unsigned int *t_addr;

int led_major=0, led_minor=0;
dev_t led_dev;
struct cdev led_cdev;
struct class *led_class;

........
{
	printk(KERN_WARNING "[led_DD]open..\n");
	
	return 0;
}

..........
{
	printk(KERN_WARNING "[led_DD]release..\n");
	return 0;
}

..........
{
	int k_data=0;
	int ret;

	printk(KERN_WARNING "[led_DD]read..\n");

	k_data = ______(GPIO_LED);

	ret = _______(buf, &k_data, count);
	if(ret < 0) return -1;

	printk(KERN_WARNING "[led_DD]read done(%d)..\n", k_data);

	return count;
}


.........
{
	int k_data;
	int ret;

	printk(KERN_WARNING "[led_DD]write..\n");

	ret = _______(&k_data, buf, count);
	if(ret < 0) return -1;
	
	if(k_data) ______(GPIO_LED);
	else _______(GPIO_LED);

	//write to device
	printk(KERN_WARNING "[led_DD]write done(%d)..\n", k_data);


	return count;
}


.........
{
	printk(KERN_WARNING "[led_DD]ioctl(cmd:%x)..\n", cmd);

	return 0;
}

struct file_operations led_fops = {
    read:       led_read,
    write:      led_write,
    open:       led_open,
//    ioctl:		led_ioctl,
    unlocked_ioctl:		led_ioctl,
    release:    led_release
};

int __init led_init(void)
{
	int error;
	void *map;

	printk("<1> LED Module id Up....\n");

	if(led_major) {
		led_dev = MKDEV(led_major, led_minor);
		error = _______________;
	} else {
		error = ________________;
		led_major = MAJOR(led_dev);
	}
	if(error < 0) {
		printk(KERN_WARNING "LED:alloc_major error!!\n");
		return error;
	}

	printk("LED:alloc_major ok! => major_num:%d\n", led_major);


	// register_chrdev
	cdev_init(&led_cdev, ________);
	led_cdev.owner = THIS_MODULE;
	error = _______________
	if(error < 0) {
		printk(KERN_WARNING "LED:register_chrdev error!!\n");
		return error;
	}
	
	led_class = class_create(THIS_MODULE, "led");
	if(IS_ERR(led_class)) {
		printk("Class Create Fail!!\n");
		cdev_del(&led_cdev);
		unregister_chrdev_region(led_dev, 1);
		return PTR_ERR(led_class);
	}
	printk("Class Create OK!!\n");
	
	device_create(led_class, NULL, led_dev, NULL, "led");
	printk("Class_Device Create OK!!\n");
	
	map = ioremap(GPIO_BASE, GPIO_SIZE);
	if(!map) {
		printk(KERN_WARNING "LED:mapping GPIO memory error!!\n");
		return -EBUSY;
	}
	gpio = (volatile unsigned int *)map;
	
	GPIO_IN(GPIO_LED);
	GPIO_OUT(GPIO_LED);

	printk(KERN_WARNING "LED Module Insert Done!!\n");
	
	return 0;
}

void __exit led_exit(void)
{
	printk("<1> LED Module id Down....\n");
		
	if(gpio) {
		iounmap(gpio);
	}
	
	cdev_del(&led_cdev);
	unregister_chrdev_region(led_dev, 1);
	device_destroy(led_class, led_dev);
	class_destroy(led_class);

	printk(KERN_WARNING "LED Module Delete Done!!\n");
}

module_init(led_init);
module_exit(led_exit);

MODULE_LICENSE("Dual BSD/GPL");
