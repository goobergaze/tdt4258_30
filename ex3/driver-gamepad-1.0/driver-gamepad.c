/*
 * This is a Linux kernel module.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/ioport.h>
#include <linux/fs.h>
#include <linux/interrupt.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/signal.h>
#include <linux/poll.h>
#include <asm/io.h>
#include "efm32gg.h"


static int my_open(struct inode*, struct file*);
static int my_release(struct inode*, struct file*);
static ssize_t my_read(struct file*, char* __user, size_t, loff_t*);
static ssize_t my_write(struct file*, const char* __user, size_t, loff_t*);
static int my_fasync(int, struct file*, int);
irqreturn_t gpio_irq_handler(int, void*);

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
	.release = my_release,
	.fasync = my_fasync
};

static struct fasync_struct *async_queue;

static uint32_t button_status = 0;


/*
 * my_driver_init - function to insert this module into kernel space
 *
 * This is the first of two exported functions to handle inserting this
 * code into a running kernel
 *
 * Returns 0 if successfull, otherwise -1
 */

static int __init my_driver_init(void)
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

	// Setting up interrupt handlers
	request_irq(IRQ_GPIO_EVEN, gpio_irq_handler, 0, DRIVER_NAME, NULL);
	request_irq(IRQ_GPIO_ODD,  gpio_irq_handler, 0, DRIVER_NAME, NULL);

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

	// Removing the parent process from async_queue
	my_fasync(-1, filp, 0);

	return 0;
}

static ssize_t my_read(struct file *filp, char __user *buff, size_t count, loff_t *offp){
	printk(KERN_INFO "Reading button status...\n");

    if (count == 0) {
		return -EINVAL;
    }

	if(count > 8 || count < 0){
		return -EFAULT;
	}

	copy_to_user(buff, &button_status, 1);
    return 1;
}

static ssize_t my_write(struct file *filp, const char __user *buff, size_t count, loff_t *offp){
	printk(KERN_INFO "Writing to buttons is not allowed.\n");
	return 1;
}

// Functions related to interrupts

static int my_fasync(int fd, struct file *filp, int mode)
{
	return fasync_helper(fd, filp, mode, &async_queue);
}

irqreturn_t gpio_irq_handler(int irq, void *dev_id)
{
	// Copy the GPIO register value to driver memory
	button_status = ioread32(GPIO_PC_DIN);

	// Issue a signal to the user processes
	kill_fasync(&async_queue, SIGIO, POLLIN | POLLRDNORM);

	return IRQ_HANDLED;
}


/*
 * my_driver_cleanup - function to cleanup this module from kernel space
 *
 * This is the second of two exported functions to handle cleanup this
 * code from a running kernel
 */

static void __exit my_driver_cleanup(void)
{
	 printk(KERN_INFO "Cleaning up the gamepad driver...\n");

	// Unmap I/O memory??

	// Releasing I/O memory regions
	release_mem_region(GPIO_PC_BASE, 0x24);
	release_mem_region(GPIO_PA_BASE + 0x100, 0x20);

	// Releasing interrupt handlers
	free_irq(IRQ_GPIO_EVEN, NULL);
	free_irq(IRQ_GPIO_ODD,  NULL);

	// Removing device from user space
	device_destroy(cl, device_number);
    class_destroy(cl);
    cdev_del(&my_cdev);

	// Freeing up the device numbers
	unregister_chrdev_region(device_number, DEVICE_COUNT);
}

module_init(my_driver_init);
module_exit(my_driver_cleanup);

MODULE_DESCRIPTION("Device driver for the gamepad.");
MODULE_LICENSE("GPL");

