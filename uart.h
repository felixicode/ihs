#ifndef __UART_H__
#define __UART_H__


#include "stdio.h"
#include "delay.h"					//�����������͵�����
/**********************ȫ�ֱ�����������**************************/
extern u8 UART_Rflag;
extern u8 UART_buff[4];		//���ý��ջ�����
extern u8 UART_num;					//���ý������ݸ�����Ҫ�Ȼ���������С
/************************������������****************************/
void UART_SendByte(u8 dat);	//�����ֽڷ��ͺ���
void UART_SendStr(u8 *s);		//�����ַ�������
void UART_init();						//UART��ʼ������

#endif 