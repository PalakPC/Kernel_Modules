/*Kernel module to print a string given as command-line argument to log.*/

/*Undefining because otherwise code gives redefinition warning on compilation.*/
#undef __KERNEL__
#undef MODULE

/*Defining __KERNEL__ and MODULE allows us to access kernel-level code not usually available to userspace programs.*/
#define __KERNEL__ 
#define MODULE
 
/*Linux Kernel/LKM headers: module.h is needed by all modules and kernel.h is needed for KERN_INFO.*/
#include <linux/module.h>	/*Included for all kernel modules.*/
#include <linux/moduleparam.h>	/*Included for module_param(). It takes command-line argument.*/
#include <linux/kernel.h>	/*Included for KERN_INFO.*/
#include <linux/init.h>	/*Included for __init and __exit macros.*/
#include <linux/string.h>     /*Included for strlen().*/
#include <linux/slab.h>  /*Included for kmalloc().*/

static char *message = "string";
module_param(message, charp, 0000);	/*To take command-line argument.*/
MODULE_PARM_DESC(message, "An array");

static int __init hello_init(void) {
   int length;
   char *pstring;
   length = strlen(message);
   pstring = kmalloc(length, GFP_KERNEL);    /*Memory allocation to string.*/
   if(pstring == NULL)
      printk(KERN_INFO "kmalloc fail\n");
   else {
      pstring = message; /*The objective was to copy the command-line argument to another string.*/
      printk(KERN_INFO "%s\n", pstring);
   }
   return 0;	/*Non-zero return means that the module couldn't be loaded.*/
}
 
static void __exit hello_cleanup(void) {
   printk(KERN_INFO "Cleaning up module.\n");
}

module_init(hello_init);
module_exit(hello_cleanup);
