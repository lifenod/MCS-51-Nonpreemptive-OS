/******************************************************************************
* File name:   os_c.c
* Author:      mwum@dreamxu.com
* Data:        2013-5-7
* Description: С�ͷ���ռʽ����ϵͳ
******************************************************************************/

#include <reg52.h>
#include "os_cfg.h"

uint16 g_os_task_delay[OS_MAX_TASK] = {0};	//����������ʱ����
/* ��������ָ�� */
static void (*code os_task[])(void) = {
	OS_TASK_NAME_TABEL
};

/* ��ʱ��0��ʼ�� */
static void os_timer0_init(void)
{
	TMOD = 0x01;			//���ö�ʱ����0ģʽһ��16λ��ʱ����
	TL0 = OS_TTASK;			//��ʼ����ʱ��0�ĵ�8λ����ֵ
	TH0 = OS_TTASK >> 8;	//��ʼ����ʱ��0�ĸ�8λ����ֵ
	TR0 = 1;				//������ʱ��0
	ET0 = 1;				//��ʱ��0�ж�ʹ��
	EA = 1;					//���жϿ��ش�
}

/* ��ʱ��0���жϷ������ */
void os_timer0_isr(void) interrupt 1
{
	unsigned char i;
	
	TL0 = OS_TTASK;			//���³�ʼ����ʱ��0�ĵ�8λ����ֵ
	TH0 = OS_TTASK >> 8;	//���³�ʼ����ʱ��0�ĸ�8λ����ֵ
	
	//ÿ���Ķ�������ʱ������1������0���������
	for (i = 0;i < OS_MAX_TASK; i++)
		if (g_os_task_delay[i])
			g_os_task_delay[i]--;
}

/* ��������ϵͳ��һ��������˲������� */
void os_run()
{
	unsigned char i;
	
	os_timer0_init();
	
	/* ������ȣ����ȼ� 0-OS_MAX_TASK �ݼ�
	 * ���ȼ����ϸ����ڲ�ѯ��������Ĺ����в����жϣ�
	 * ������������ʱ��һ������0��ִ�� */
	while (1) {
		for (i = 0; i < OS_MAX_TASK; i++) {
			if (g_os_task_delay[i] == 0) {
				os_task[i]();
				break;		//���ȼ���ʵ��
			}
		}
	}
}