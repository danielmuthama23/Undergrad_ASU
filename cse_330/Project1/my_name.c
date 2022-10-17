// file: /home/tyler/project_1/my_name.c

#include <linux/module.h>
#include <linux/kernel.h>

int my_name_init(void) {
	printk("[Group-44][Tyler Fichiera, Ethan Robinson, Ryan Dillon], Hello I am Tyler Fichiera, a student of CSE 330 Fall 2022\n");
	return 0;
}

void my_name_exit(void) {
	printk("Goodbye-Tyler Fichiera\n");
}
 
/*We need at least two functions in a module, init and exit. Init function is called when the module is 
loaded (insmod) into the kernel, and exit function is called when the module is removed from the kernel 
(rmmod).*/
 
module_init(my_name_init); //defines the hello_init to be called at module load
module_exit(my_name_exit); // defines the hello_exit to be called at module unload 
MODULE_LICENSE("GPL");   // defines license of the module
