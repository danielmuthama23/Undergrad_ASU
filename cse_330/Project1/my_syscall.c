// file: /linux-5.16/my_syscall/my_syscall.c

#include <linux/kernel.h>
#include <linux/syscalls.h>

SYSCALL_DEFINE0(my_syscall)
{
	printk("This is the new system call FichieraRobinsonDillon implemented.\n");
	return 0;
}
