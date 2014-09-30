/*Kernel module to print "Hello World!" to log.*/

/*Undefining because otherwise code gives redefinition warning on compilation.*/
#undef __KERNEL__
#undef MODULE

/*Defining __KERNEL__ and MODULE allows us to access kernel-level code not usually available to userspace programs.*/
#define __KERNEL__
#define MODULE
 
/*Linux Kernel/LKM headers: module.h is needed by all modules and kernel.h is needed for KERN_INFO.*/
#include <linux/module.h>	/*Included for all kernel modules.*/
#include <linux/kernel.h>	/*Included for KERN_INFO.*/
#include <linux/init.h>	/*Included for __init and __exit macros.*/
 
static int __init hello_init(void) {
   printk(KERN_INFO "Hello world!\n");
   return 0;	/*Non-zero return means that the module couldn't be loaded.*/
}
 
static void __exit hello_cleanup(void) {
   printk(KERN_INFO "Cleaning up module.\n");
}
 
module_init(hello_init);
module_exit(hello_cleanup); 
