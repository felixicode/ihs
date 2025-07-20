#ifndef __UART_H__
#define __UART_H__


#include "stdio.h"
#include "delay.h"					//包含数据类型的引用
/**********************全局变量定义区域**************************/
extern u8 UART_Rflag;
extern u8 UART_buff[4];		//设置接收缓冲区
extern u8 UART_num;					//设置接收数据个数，要比缓冲数组规格小
/************************函数声明区域****************************/
void UART_SendByte(u8 dat);	//单个字节发送函数
void UART_SendStr(u8 *s);		//发送字符串函数
void UART_init();						//UART初始化函数

#endif 