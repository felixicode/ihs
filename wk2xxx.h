#ifndef	__WK2XXX_H       
#define __WK2XXX_H

//#include "STC8H.h"
#include "delay.h"			//包含数据类型的引用
#include "string.h"
#include "UART.h"
/**************************晶振频率定义***************************/
#define FOSE_SELECT    1//1选择WK2XXX晶振频率使用7.3728MHz，0则使用使用11.0592MHz
#if FOSE_SELECT
#define FOSE_7_3728MHz	//WK2XXX晶振频率使用7.3728MHz
#else 
#define FOSE_11_0592MHz	//WK2XXX晶振频率使用11.0592MHz
#endif

#define IHS_UART_PRINT 1
#define IHS_UART_EC 2

/**********************WK2xxx的寄存器地址*************************/
//全局寄存器地址
#define 	WK2XXX_GENA     0x00
#define 	WK2XXX_GRST     0x01
#define		WK2XXX_GMUT     0x02
#define 	WK2XXX_GIER     0x10
#define 	WK2XXX_GIFR     0x11
#define 	WK2XXX_GPDIR    0x21
#define 	WK2XXX_GPDAT    0x31
//子串口控制寄存器地址
#define 	WK2XXX_SPAGE    0x03
//PAGE0
#define 	WK2XXX_SCR      0x04
#define 	WK2XXX_LCR      0x05
#define 	WK2XXX_FCR      0x06
#define 	WK2XXX_SIER     0x07
#define 	WK2XXX_SIFR     0x08
#define 	WK2XXX_TFCNT    0x09
#define 	WK2XXX_RFCNT    0x0A
#define 	WK2XXX_FSR      0x0B
#define 	WK2XXX_LSR      0x0C
#define 	WK2XXX_FDAT     0x0D
#define 	WK2XXX_FWCR     0x0E
#define 	WK2XXX_RS485    0x0F
//PAGE1
#define 	WK2XXX_BAUD1    0x04
#define 	WK2XXX_BAUD0    0x05
#define 	WK2XXX_PRES     0x06
#define 	WK2XXX_RFTL     0x07
#define 	WK2XXX_TFTL     0x08
#define 	WK2XXX_FWTH     0x09
#define 	WK2XXX_FWTL     0x0A
#define 	WK2XXX_XON1     0x0B
#define 	WK2XXX_XOFF1    0x0C
#define 	WK2XXX_SADR     0x0D
#define 	WK2XXX_SAEN     0x0E
#define 	WK2XXX_RTSDLY   0x0F
//WK2xxx寄存器位定义
// GENA
#define 	WK2XXX_UT4EN	0x08
#define 	WK2XXX_UT3EN	0x04
#define 	WK2XXX_UT2EN	0x02
#define 	WK2XXX_UT1EN	0x01
//GRST
#define 	WK2XXX_UT4SLEEP	0x80
#define 	WK2XXX_UT3SLEEP	0x40
#define 	WK2XXX_UT2SLEEP	0x20
#define 	WK2XXX_UT1SLEEP	0x10
#define 	WK2XXX_UT4RST	0x08
#define 	WK2XXX_UT3RST	0x04
#define 	WK2XXX_UT2RST	0x02
#define 	WK2XXX_UT1RST	0x01
//GIER
#define 	WK2XXX_UT4IE	0x08
#define 	WK2XXX_UT3IE	0x04
#define 	WK2XXX_UT2IE	0x02
#define 	WK2XXX_UT1IE	0x01
//GIFR
#define 	WK2XXX_UT4INT	0x08
#define 	WK2XXX_UT3INT	0x04
#define 	WK2XXX_UT2INT	0x02
#define 	WK2XXX_UT1INT	0x01
//SPAGE
#define 	WK2XXX_SPAGE0	0x00
#define 	WK2XXX_SPAGE1   0x01
//SCR
#define 	WK2XXX_SLEEPEN	0x04
#define 	WK2XXX_TXEN     0x02
#define 	WK2XXX_RXEN     0x01
//LCR
#define 	WK2XXX_BREAK	0x20
#define 	WK2XXX_IREN     0x10
#define 	WK2XXX_PAEN     0x08
#define 	WK2XXX_PAM1     0x04
#define 	WK2XXX_PAM0     0x02
#define 	WK2XXX_STPL     0x01
//FCR
//SIER
#define 	WK2XXX_FERR_IEN      0x80
#define 	WK2XXX_CTS_IEN       0x40
#define 	WK2XXX_RTS_IEN       0x20
#define 	WK2XXX_XOFF_IEN      0x10
#define 	WK2XXX_TFEMPTY_IEN   0x08
#define 	WK2XXX_TFTRIG_IEN    0x04
#define 	WK2XXX_RXOUT_IEN     0x02
#define 	WK2XXX_RFTRIG_IEN    0x01
//SIFR
#define 	WK2XXX_FERR_INT      0x80
#define 	WK2XXX_CTS_INT       0x40
#define 	WK2XXX_RTS_INT       0x20
#define 	WK2XXX_XOFF_INT      0x10
#define 	WK2XXX_TFEMPTY_INT   0x08
#define 	WK2XXX_TFTRIG_INT    0x04
#define 	WK2XXX_RXOVT_INT     0x02
#define 	WK2XXX_RFTRIG_INT    0x01
//TFCNT
//RFCNT
//FSR
#define 	WK2XXX_RFOE     0x80
#define 	WK2XXX_RFBI     0x40
#define 	WK2XXX_RFFE     0x20
#define 	WK2XXX_RFPE     0x10
#define 	WK2XXX_RDAT     0x08
#define 	WK2XXX_TDAT     0x04
#define 	WK2XXX_TFULL    0x02
#define 	WK2XXX_TBUSY    0x01
//LSR
#define 	WK2XXX_OE       0x08
#define 	WK2XXX_BI       0x04
#define 	WK2XXX_FE       0x02
#define 	WK2XXX_PE       0x01
//FWCR
//RS485
#ifdef  FOSE_11_0592MHz //11.0592Mhz晶振下WK2xxx的波特率
#define WK2XXX_BAUD_230400 0x0002 
#define WK2XXX_BAUD_115200 0x0005
#define WK2XXX_BAUD_57600  0x000b
#define WK2XXX_BAUD_28800  0x0017 
#define WK2XXX_BAUD_14400  0x002f 
#define WK2XXX_BAUD_7200   0x005f 
#define WK2XXX_BAUD_3600   0x00bf 
#define WK2XXX_BAUD_1800   0x0017f
#define WK2XXX_BAUD_691200 0x0000 
#define WK2XXX_BAUD_345600 0x0001 
#define WK2XXX_BAUD_172800 0x0003 
#define WK2XXX_BAUD_86400  0x0007 
#define WK2XXX_BAUD_43200  0x000f 
#define WK2XXX_BAUD_21600  0x001f
#define WK2XXX_BAUD_10800  0x003f
#define WK2XXX_BAUD_5400   0x007f
#endif
#ifdef FOSE_7_3728MHz //7.3728Mhz晶振下WK2xxx的波特率
#define WK2XXX_BAUD_153600 0x0002 
#define WK2XXX_BAUD_76800  0x0005
#define WK2XXX_BAUD_38400  0x00b
#define WK2XXX_BAUD_19200  0x0017 
#define WK2XXX_BAUD_9600   0x002f 
#define WK2XXX_BAUD_4800   0x005f 
#define WK2XXX_BAUD_2400   0x00bf 
#define WK2XXX_BAUD_1200   0x0017f
#define WK2XXX_BAUD_460800 0x0000 
#define WK2XXX_BAUD_230400 0x0001 
#define WK2XXX_BAUD_115200 0x0003 
#define WK2XXX_BAUD_57600  0x0007 
#define WK2XXX_BAUD_28800  0x000f 
#define WK2XXX_BAUD_14400  0x001f
#define WK2XXX_BAUD_7200   0x003f
#define WK2XXX_BAUD_3600   0x007f
#endif
/***********************WK2XXX函数声明区****************************/
//初始化调用
void WK2XXX_Init(void);
//WK2XXX初始化函数
void WK2XXX_UTx_Init(u8 num,u16 baud);
//WK2XXX子串口初始化函数
//读写寄存器/FIFO调用
u8 WK2XXX_Read_GlobalREG(u8 reg);
//WK2XXX读全局寄存器函数
void WK2XXX_Write_GlobalREG(u8 reg,u8 dat);
//WK2XXX写全局寄存器函数
u8 WK2XXX_Read_REG(u8 num,u8 reg);
//WK2XXX读子串口寄存器函数
void WK2XXX_Write_REG(u8 num,u8 reg,u8 dat);
//WK2XXX写子串口寄存器函数
void WK2XXX_Read_FIFO(u8 num,u8 count,u8 *fifo_buff);
//WK2XXX读FIFO函数
void WK2XXX_Write_FIFO(u8 num,u8 count,u8 *fifo_buff);
//WK2XXX写FIFO函数
//写寄存器方式收发数据调用
void WK2XXX_Write_REG_SendString(u8 num,u8 *buff);
//WK2XXX发送字符串函数
u8 WK2XXX_Write_REG_ReceiveByte(u8 num);
//WK2XXX写寄存器方式接收数据函数
void WK2XXX_Write_REG_SendByte(u8 num,u8 dat);
//WK2XXX写寄存器方式发送数据函数
void WK2XXX_REG_Receive_And_Send(u8 num);
//WK2XXX写寄存器方式数据收发一体函数
//写FIFO方式收发数据调用
void WK2XXX_Write_FIFO_ReceiveData(u8 num,u8 *fifo_buff);
//写FIFO方式发送数据函数
void WK2XXX_Write_FIFO_SendData(u8 num,u8 *fifo_buff);
//写FIFO方式接收数据函数

#endif
