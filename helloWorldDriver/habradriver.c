#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

MODULE_LICENSE( "GPL" );
MODULE_AUTHOR( "ANDRES" );
MODULE_DESCRIPTION( "just module" );
MODULE_SUPPORTED_DEVICE("test");

#define SUCCESS 0
#define DEVICE_NAME "test"

static int device_open(struct inode*, struct file* );
static int device_release(struct inode*, struct file* );
static ssize_t device_read(struct file*, char*, size_t, loff_t* );
static ssize_t device_write(struct file* ,const char* , size_t, loff_t*);

static int major_number;
static int is_device_open = 0;
static char text[5] = "test\n";
static char* text_ptr = text;

static struct file_operations fops = 
{
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release
};

static int __init test_init(void)
{
		printk("TEST driver is loaded!\n");
		
		major_number = register_chrdev(0, DEVICE_NAME, &fops );
		
		if (major_number < 0)
		{
			printk("Unsuccess register with: %d\n", major_number);
			return major_number;
		}
		
		printk("Module loaded, type command: sudo mknod /dev/test c %d 0\n", major_number);
		
		return SUCCESS;
		
}

static void __exit test_exit(void)
{
	printk("Unloading!\n");
	
	unregister_chrdev(major_number, DEVICE_NAME);
	
	printk("Unloaded.\n");
	
	return;
}

module_init(test_init);
module_exit(test_exit);

static int device_open(struct inode* inode, struct file* file)
{
	text_ptr = text;

	if(is_device_open)
		return -EBUSY;

	is_device_open++;
	return SUCCESS;
}

static int device_release(struct inode* inode, struct file* file)
{
	is_device_open--;
	return SUCCESS;
} 

static ssize_t device_write(struct file* filp, const char* buf, size_t length, loff_t* offset)
{
	printk("Unsupported operation!\n");
	return -EINVAL;
}

static ssize_t device_read(struct file* filp, char* buf, size_t length, loff_t* offset )
{
	int byte_read = 0;
	int ret = 0;
	
	if(text_ptr ==0)
		return 0;
		
	while(length && *text_ptr != 0)
	{
		ret = put_user( *( text_ptr++ ), buf++ );
		
		if(ret != 0)
			return byte_read;
			
		length--;
		byte_read++;
	}
	return byte_read;
}
