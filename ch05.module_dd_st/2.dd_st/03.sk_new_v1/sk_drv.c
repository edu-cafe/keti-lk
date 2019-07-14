#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#include <linux/fs.h>

#include <linux/cdev.h>			// struct cdev, ..
#include <linux/device.h>		//struct class,...

int sk_major=0, sk_minor=3;
dev_t sk_dev;
struct cdev sk_cdev;

int sk_open (struct inode *inode, struct file *filp)
{
	printk(KERN_WARNING "[SK_DD]open..\n");
	
	return 0;
}

int sk_release (struct inode *inode, struct file *filp)
{
	printk(KERN_WARNING "[SK_DD]release..\n");
	return 0;
}

ssize_t sk_read (struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
	printk(KERN_WARNING "[SK_DD]read..\n");
	return count;
}


ssize_t sk_write (struct file *filp, const char __user *buf, size_t count, loff_t *f_pos)
{
	printk(KERN_WARNING "[SK_DD]write..\n");
	return count;
}


//int sk_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)
long sk_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	printk(KERN_WARNING "[SK_DD]ioctl..\n");
	return 0;
}

struct class *sk_class;

struct file_operations sk_fops = {
    read:       sk_read,
    write:      sk_write,
    open:       sk_open,
//    ioctl:		sk_ioctl,
    unlocked_ioctl:		sk_ioctl,
    release:    sk_release
};

int sk_init(void)
{
	int error;

	printk("<1> SK Module id Up....\n");

	if(sk_major) {
		sk_dev = MKDEV(sk_major, sk_minor);
		error = register_chrdev_region(sk_dev, 1, "sk");
	} else {
		error = alloc_chrdev_region(&sk_dev, sk_minor, 1, "sk");
		sk_major = MAJOR(sk_dev);
	}
	if(error < 0) {
		printk(KERN_WARNING "sk:alloc_major error!!\n");
		return error;
	}

	printk("<1> sk:alloc_major ok! => major_num:%d\n", sk_major);

	// register_chrdev
	cdev_init(&sk_cdev, &sk_fops);
	sk_cdev.owner = THIS_MODULE;
	error = cdev_add(&sk_cdev, sk_dev, 1);
	if(error < 0) {
		printk(KERN_WARNING "sk:register_chrdev error!!\n");
		return error;
	}
	
	sk_class = class_create(THIS_MODULE, "sk");
	if(IS_ERR(sk_class)) {
		printk("Class Create Fail!!\n");
		cdev_del(&sk_cdev);
		unregister_chrdev_region(sk_dev, 1);
		return PTR_ERR(sk_class);
	}
	printk("Class Create OK!!\n");
	
	device_create(sk_class, NULL, sk_dev, NULL, "sk");
	printk("Class_Device Create OK!!\n");

	printk(KERN_WARNING "SK Module Insert Done!!\n");
	return 0;
}

void sk_exit(void)
{
	printk("<1> SK Module id Down....\n");

	cdev_del(&sk_cdev);
	unregister_chrdev_region(sk_dev, 1);
	device_destroy(sk_class, sk_dev);
	class_destroy(sk_class);

	printk(KERN_WARNING "SK Module Delete Done!!\n");
}

module_init(sk_init);
module_exit(sk_exit);

MODULE_LICENSE("Dual BSD/GPL");
