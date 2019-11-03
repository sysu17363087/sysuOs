#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
#include <linux/sched/task.h>

#define __NR_myprocess 300
struct task_struct *pcurrent;
struct task_struct *task;
asmlinkage int sys_myprocess(void)
{
pcurrent = get_current();
printk(KERN_INFO "Current :\n pid : %d\n",current->pid);/*当前进程PID*/
printk(KERN_INFO "Task state: %d\n",current->state);/*运行状态，-1为不可运行，0为可运行，>0为运行结束*/
printk(KERN_INFO "Task name: %s\n",current->comm);/*进程名*/
printk(KERN_INFO "Start time:%.24s %1d\n",(current->start_time).tv_sec,(current->start_time).tv_nsec);/*进程开始时间，timespec是纳米级时间，是一个结构体 其定义为：struct timespec             {time_t tv_sec; long tv_nsec;   };*/
int i=0;
for(task=current->parent;task!=&init_task;task=task->parent)
{/*输出父进程直到init*/
    i=i+1;
    printk(KERN_INFO "%d parent pid:%d\n",i,task->pid);
}
printk(KERN_INFO "END By linfeng!\n");
return 1;
}

