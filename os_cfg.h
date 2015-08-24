/******************************************************************************
* File name:   os_cfg.c
* Author:      mwum@dreamxu.com
* Data:        2013-5-7
* Description: os_c.c的头文件，系统的配置文件
******************************************************************************/

#ifndef _OS_CFG_H
#define _OS_CFG_H

#define OS_MAX_TASK		4							//定义任务数量
#define FOSC			12000000					//定义晶振频率（Hz）
#define OS_FTASK		1000						//定义任务时钟频率（Hz）
#define OS_TTASK		(65536-FOSC/12/OS_FTASK)	//计算定时器时间12T模式下
/* 定义任务名称列表 */
#define OS_TASK_NAME_TABEL	\
		os_task0,			\
		os_task1,			\
		os_task2,			\
		os_task3,

/* 任务优先级从0-3递减 */
extern void os_task0(void);
extern void os_task1(void);
extern void os_task2(void);
extern void os_task3(void);

#define uint16 unsigned int

//以下不需要更改
/* 定义任务执行频率，即任务每 1/OS_TASK_FRE(f)秒 执行一次 */
#define OS_TASK_FRE(f)	(OS_FTASK/(f))
extern void os_run();
extern uint16 g_os_task_delay[OS_MAX_TASK];


#endif