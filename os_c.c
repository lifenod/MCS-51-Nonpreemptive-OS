/******************************************************************************
* File name:   os_c.c
* Author:      mwum@dreamxu.com
* Data:        2013-5-7
* Description: 小型非抢占式操作系统
******************************************************************************/

#include <reg52.h>
#include "os_cfg.h"

uint16 g_os_task_delay[OS_MAX_TASK] = {0};	//定义任务延时变量
/* 定义任务指针 */
static void (*code os_task[])(void) = {
	OS_TASK_NAME_TABEL
};

/* 定时器0初始化 */
static void os_timer0_init(void)
{
	TMOD = 0x01;			//设置定时器在0模式一（16位定时器）
	TL0 = OS_TTASK;			//初始化定时器0的低8位计数值
	TH0 = OS_TTASK >> 8;	//初始化定时器0的高8位计数值
	TR0 = 1;				//启动定时器0
	ET0 = 1;				//定时器0中断使能
	EA = 1;					//总中断开关打开
}

/* 定时器0的中断服务程序 */
void os_timer0_isr(void) interrupt 1
{
	unsigned char i;
	
	TL0 = OS_TTASK;			//重新初始化定时器0的低8位计数值
	TH0 = OS_TTASK >> 8;	//重新初始化定时器0的高8位计数值
	
	//每节拍对任务延时变量减1，减至0后，任务就绪
	for (i = 0;i < OS_MAX_TASK; i++)
		if (g_os_task_delay[i])
			g_os_task_delay[i]--;
}

/* 启动操作系统，一旦进入就退不出来了 */
void os_run()
{
	unsigned char i;
	
	os_timer0_init();
	
	/* 任务调度，优先级 0-OS_MAX_TASK 递减
	 * 优先级不严格，若在查询就绪任务的过程中产生中断，
	 * 多个任务就绪的时候不一定任务0先执行 */
	while (1) {
		for (i = 0; i < OS_MAX_TASK; i++) {
			if (g_os_task_delay[i] == 0) {
				os_task[i]();
				break;		//优先级的实现
			}
		}
	}
}