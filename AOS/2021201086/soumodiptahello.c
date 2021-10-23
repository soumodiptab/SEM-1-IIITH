#include <linux/syscalls.h>
#include <linux/kernel.h>
SYSCALL_DEFINE0(soumodiptahello)
{
	printk("Welcome to Syscall Programming.\n");
	return 0;
}
