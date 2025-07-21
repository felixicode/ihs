#ifndef __DELAY_H__
#define __DELAY_H__

/************************�����������Ͷ���*************************/
#define u8  uint8_t
#define u16 uint16_t
#define u32 uint32_t 
typedef unsigned char    uint8_t;
typedef unsigned short   uint16_t;
typedef unsigned long    uint32_t;
/***************************����������****************************/
void delay_us(u16 t);		//us����ʱ����
void delay_ms(u16 t);		//ms����ʱ����
void delay_s(u16 t);		// s����ʱ����

#endif 