#include <linux/syscalls.h>
#include <linux/kernel.h>
SYSCALL_DEFINE1(soumodiptaprint, char __user *,data)
{
	printk("Hello there  %s !\n",data);
    	return 0;
}
