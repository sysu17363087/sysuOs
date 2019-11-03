#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/init_task.h>
// 初始化函数
static int hello_init(void)
{
    struct task_struct	*p;
    p = NULL;
    p = &init_task;

    for_each_process(p)
    {
        if(p->mm == NULL){ //内核线程的mm成员为空
		struct sched_entity se;
		se = p->se;

	printk(KERN_ALERT"se.exec_start\t \t %llu\n",se.exec_start);
	printk(KERN_ALERT"se.sum_exec_runtime\t \t %llu\n",se.sum_exec_runtime);
	printk(KERN_ALERT"se.vruntime\t \t %llu\n",se.vruntime);
	printk(KERN_ALERT"se.prev_sum_exec_runtime\t  \t %llu\n",se.prev_sum_exec_runtime);
	printk(KERN_ALERT"se.nr_migrations\t \t %llu\n",se.nr_migrations);
        }
    }
    return 0;
}
// 清理函数
static void hello_exit(void)
{
    printk(KERN_ALERT"goodbye!\n");
}
 
// 函数注册
module_init(hello_init);  
module_exit(hello_exit);  
 
// 模块许可申明
MODULE_LICENSE("GPL");
