#ifndef __DELAY_H__
#define __DELAY_H__

/************************常用数据类型定义*************************/
#define u8  uint8_t
#define u16 uint16_t
#define u32 uint32_t 
typedef unsigned char    uint8_t;
typedef unsigned short   uint16_t;
typedef unsigned long    uint32_t;
/***************************函数声明区****************************/
void delay_us(u16 t);		//us级延时函数
void delay_ms(u16 t);		//ms级延时函数
void delay_s(u16 t);		// s级延时函数

#endif 