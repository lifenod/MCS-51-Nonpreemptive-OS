/******************************************************************************
* File name:   os_c.c
* Author:      mwum@dreamxu.com
* Data:        2013-5-7
* Description: ����ϵͳ����LED����˸
*              ����1��LED1 ��20ms ��20ms ѭ��
*              ����2��LED2 ��50ms ��50ms ѭ��
*              ����3��LED3 ��10ms ��10ms ѭ��
*              ����4��LED4 ��20ms ��10ms ѭ��
******************************************************************************/

#include <reg52.H>
#include "os_cfg.h"

#define LED	P1
sbit LED1 = P1^0;
sbit LED2 = P1^1;
sbit LED3 = P1^2;
sbit LED4 = P1^3;

void main(void)
{
	LED = 0xff;		//��ʼ��LED�ƣ�ȫ��
	
	os_run();
}

void os_task0(void)
{
	LED1 = !LED1;
	g_os_task_delay[0] = OS_TASK_FRE(50);
}

void os_task1(void)
{
	LED2 = !LED2;
	g_os_task_delay[1] = OS_TASK_FRE(20);
}

void os_task2(void)
{
	LED3 = !LED3;
	g_os_task_delay[2] = OS_TASK_FRE(100);
}

/* ״̬��˼�룬ʵ����������ʱ����һ��������ֳɶ�Σ� */
void os_task3(void)
{
	static unsigned char s_os_delay_state=0;
	
	switch (s_os_delay_state) {
	case 0:
		LED4 = 0;
		s_os_delay_state = 1;
		g_os_task_delay[3] = OS_TASK_FRE(50);
		break;
	case 1:
		LED4 = 1;  
		s_os_delay_state = 0;
		g_os_task_delay[3] = OS_TASK_FRE(100);
		break;
	default:
		break;
	}	
}