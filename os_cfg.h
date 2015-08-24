/******************************************************************************
* File name:   os_cfg.c
* Author:      mwum@dreamxu.com
* Data:        2013-5-7
* Description: os_c.c��ͷ�ļ���ϵͳ�������ļ�
******************************************************************************/

#ifndef _OS_CFG_H
#define _OS_CFG_H

#define OS_MAX_TASK		4							//������������
#define FOSC			12000000					//���徧��Ƶ�ʣ�Hz��
#define OS_FTASK		1000						//��������ʱ��Ƶ�ʣ�Hz��
#define OS_TTASK		(65536-FOSC/12/OS_FTASK)	//���㶨ʱ��ʱ��12Tģʽ��
/* �������������б� */
#define OS_TASK_NAME_TABEL	\
		os_task0,			\
		os_task1,			\
		os_task2,			\
		os_task3,

/* �������ȼ���0-3�ݼ� */
extern void os_task0(void);
extern void os_task1(void);
extern void os_task2(void);
extern void os_task3(void);

#define uint16 unsigned int

//���²���Ҫ����
/* ��������ִ��Ƶ�ʣ�������ÿ 1/OS_TASK_FRE(f)�� ִ��һ�� */
#define OS_TASK_FRE(f)	(OS_FTASK/(f))
extern void os_run();
extern uint16 g_os_task_delay[OS_MAX_TASK];


#endif