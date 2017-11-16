/*
 * This is a demo Linux kernel module.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/ioport.h>

/*
 * template_init - function to insert this module into kernel space
 *
 * This is the first of two exported functions to handle inserting this
 * code into a running kernel
 *
 * Returns 0 if successfull, otherwise -1
 */

/*TODO: Implement read,write,open*/


static int driver_open(struct inode *inode, struct file *filp);
static int driver_release (struct inode *inode, struct file *filp);
static ssize_t driver_read(struct file *filp, char _user *buff, size_t count, loff__t *offp);
static ssize_t driver_write(struct file*filp, const char _user *buff, size_t count, loff_t *offp);

dev_t dev = 0;
unsigned int count = 1;
static struct cdev driver_cdev = {};


struct file_operations driver_fops = {
	.owner = THIS_MODULE,
	.open = driver_open,
	.read = driver_read,
	.write = driver_write,
	.release = driver_release
};


static int __init driver_init(void)
{
	
	/*TODO:
	1. ALLOCKATE 
	2. ACCSES
	3. INITILIZE (som øv.2)
	4. REGISTER DEVICE IN SYSTEM
	*/

	int alloc__chrdev_region(&dev, 0, count, "Buttons");

	reguest_region(unsigned long first, 172, "Buttons"); 
	/*want to make use of n ports, starting with first. Name parameter should be named after the device. 
	Return non-NULL if succes, if it returns NULL ports will not be availabel... Adde noen if ?
	*/

	/*inizilaise the PIO like in ex.2*/

	cdev_init(&driver_cdev, &driver_fops);
	driver_cdev.owner = THIS_MODULE;
	cdev_add(&driver_cdev, dev, count);

	printk("Hello peepz, here is your module speaking\n");
	return 0;
}




static void __exit driver_cleanup(void)
{
	 printk("Short step for a module, long step for a short module...\n");
}


/*static int driver_open (struct inode *inode, struct file *filp)
{
	return 0;
}



static int driver_release (struct inode *inode, struct file *filp)
{
	return 0;
}



static ssize_t driver_read(struct file *filp, char _user *buff, size_t count, loff_t *offp)
{
	char output;
	/*read buttons
	if (count == 0) 
		return 0;
	....
	
}



static ssize_t driver_write(struct file *filp, const char _user *buff, size_t count, loff_t *offp)
{
	char input;
	if(count == 0)
		return 0;
	... 
}
*/


module_init(template_init);
module_exit(template_cleanup);

MODULE_DESCRIPTION("Small module, demo only, not very useful.");
MODULE_LICENSE("GPL");

