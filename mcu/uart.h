#ifndef __UART_H__
#define __UART_H__

//#include "STC8H.h"
#include "stdio.h"
#include "delay.h"					//�����������͵�����
/**********************ȫ�ֱ�����������**************************/
extern xdata u8 UART_Rflag;
extern xdata u8 UART_buff[16];		//���ý��ջ�����
extern xdata u8 UART_num;					//���ý������ݸ�����Ҫ�Ȼ���������С
/************************������������****************************/
void UART_SendByte(u8 dat);	//�����ֽڷ��ͺ���
//void UART_SendStr(u8 *s);		//�����ַ�������
void UART_init();						//UART��ʼ������

#endif 