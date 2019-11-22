
#include <stdio.h>
#include <errno.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/param.h>
#include <linux/jiffies.h>
#include <asm/system.h>
#include <asm/processor.h>
#include <asm/signal.h>
#include <linux/completion.h>       // for DECLARE_COMPLETION()
#include <linux/sched.h>            
#include <linux/delay.h>            // mdelay()
#include <linux/kthread.h> 

static struct task_struct *kthread1;
static struct task_struct *kthread2;
static struct task_struct *kthread3;

int kthread1_fuction(void *arg)
{
	return 0;
}

int kthread2_fuction(void *arg)
{
	return 0;
}

int kthread3_fuction(void *arg)
{
	return 0;
}

int main(int argc, char **argv)
{
	kthread1 = kthread_run(kthread1_fuction, NULL, "kthread1");
	kthread2 = kthread_run(kthread2_fuction, NULL, "kthread2");
	kthread3 = kthread_run(kthread3_fuction, NULL, "kthread3");

    return 0;
}
