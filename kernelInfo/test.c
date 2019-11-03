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
    printk(KERN_ALERT"exec_start\tsum_exec_runtime\tvruntime\tprev_sum_exec_runtime\tnr_migrations\t");
    for_each_process(p)
    {
        if(p->mm == NULL){ //内核线程的mm成员为空
		struct sched_entity *se;
		se = NULL;
		se = &(p.sched_entity);
		            
	printk(KERN_ALERT"%ld\t%ld\t%ld\t%ld\t%ld\n",se->exec_start,se->sum_exec_runtime,se->vruntime,se->prev_sum_exec_runtime,se->nr_migrations);
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
