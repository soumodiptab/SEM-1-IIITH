#include <linux/syscalls.h>
#include <linux/kernel.h>
#include <linux/cred.h>
SYSCALL_DEFINE0(soumodiptaprocess)
{
	struct task_struct *parent_proc = current->parent;
	printk("Parent Process ID : %d\n",parent_proc->pid);
        printk("Current Process ID : %d\n",current->pid);
        return 0;
}
