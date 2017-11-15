/*
 * This is a Linux kernel module.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <efm32gg.h>
#include <linux/ioport.h>
#include <linux/fs.h>
#include <linux/interrupt.h>
#include <linux/cdev.h>



int my_open(struct inode*, struct file*);
int my_release(struct inode*, struct file*);
ssize_t my_read(struct file*, char* __user, size_t, loff_t*);
ssize_t my_write(struct file*, char* __user, size_t, loff_t*);

#define DRIVER_NAME "gamepad"
#define DEVICE_COUNT 1
#define IRQ_GPIO_EVEN 17
#define IRQ_GPIO_ODD 18

struct cdev my_cdev;
struct class *cl;
dev_t device_number;

// Registration of file operations 
static struct file_operations my_fops = {
	.owner = THIS_MODULE,
	.read = my_read,
	.write = my_write,
	.open = my_open,
	.release = my_release
};


/*
 * driver_init - function to insert this module into kernel space
 *
 * This is the first of two exported functions to handle inserting this
 * code into a running kernel
 *
 * Returns 0 if successfull, otherwise -1
 */

static int __init driver_init(void)
{
	printk(KERN_INFO "Initializing the gamepad driver...\n");

	// Dynamically allocating device numbers
	if (alloc_chrdev_region(&device_number, 0, DEVICE_COUNT, DRIVER_NAME) < 0){
		printk(KERN_ALERT "Unable to allocate char device.\n");
	}

	// Allocating access to the I/O hardware registers
	if (request_mem_region(GPIO_PC_BASE, 0x24, DRIVER_NAME) == NULL ) {
        printk(KERN_ALERT "Unable to access the I/O-Port C memory region.\n");
        return -1;
    }
    if (request_mem_region(GPIO_PA_BASE + 0x100, 0x20, DRIVER_NAME) == NULL ) {
        printk(KERN_ALERT "Unable to access the I/O-GPIO memory region.\n");
        return -1;
    }
    
    // Memory mapping the allocated I/O regions
	if (ioremap_nocache(GPIO_PC_BASE, 0x24) == NULL){
		printk(KERN_ERR "I/O-Port C memory mapping failed\n");
	}

	if (ioremap_nocache(GPIO_PA_BASE + 0x100, 0x20) == NULL) {
		printk(KERN_ERR "I/O-GPIO memory mapping failed\n");
	}

	// Initializing hardware and setup for interrupts
	iowrite32(0x33333333, GPIO_PC_MODEL);
    iowrite32(0xFF, GPIO_PC_DOUT);

    iowrite32(0x22222222, GPIO_EXTIPSELL);
    //Mer interrupt setup



    // Initializing char device structure
    cdev_init(&my_cdev, &my_fops);
    my_cdev.owner = THIS_MODULE;
    cdev_add(&my_cdev, device_number, DEVICE_COUNT);

    // Making the driver visible to user space
    cl = class_create(THIS_MODULE, DRIVER_NAME);
    device_create(cl, NULL, device_number, NULL, DRIVER_NAME);



	return 0;
}

// Implementing the file functions we need

static int my_open(struct inode *inode, struct file *filp){
	printk(KERN_INFO "Opening driverfile...\n");
	return 0;
}

static int my_release(struct inode *inode, struct file *filp){
	printk(KERN_INFO "Closing driverfile...\n");
	return 0;
}

static ssize_t my_read(struct file *filp, char __user *buff, size_t count, loff_t *offp){
	printk(KERN_INFO "Reading button status...\n");
	uint32_t button_status = ioread32(GPIO_PC_DIN);
    copy_to_user(buff, &button_status, 1);
    return 1;
}

static ssize_t my_write(struct file *filp, const char --user *buff, size_t count, loff_t *offp){
	printk(KERN_INFO "Writing to buttons is not allowed.\n")
	return 1;
}


/*
 * driver_cleanup - function to cleanup this module from kernel space
 *
 * This is the second of two exported functions to handle cleanup this
 * code from a running kernel
 */

static void __exit driver_cleanup(void)
{
	 printk(KERN_INFO "Cleaning up the gamepad driver...\n");

	// Unmap I/O memory??

	// Releasing I/O memory regions
	release_mem_region(GPIO_PC_BASE, 0x24);
	release_mem_region(GPIO_PA_BASE + 0x100, 0x20);

	// Removing device from user space
	device_destroy(cl, device_number);
    class_destroy(cl);
    cdev_del(&my_cdev);

	// Freeing up the device numbers
	unregister_chrdev_region(device_number, DEVICE_COUNT);
}

module_init(driver_init);
module_exit(driver_cleanup);

MODULE_DESCRIPTION("Device driver for the gamepad.");
MODULE_LICENSE("GPL");

