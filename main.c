//#include <reg52.h>
#include <string.h>
//#include "STC8H.h"
#include "STC89C5xRC.H"
#include "intrins.h"
#include "dbg.h"
//#include "ec.h"

#include "uart.h"
#include "wk2xxx.h"

void delay_s(unsigned int n)
{
	   unsigned int i, j;

	   for (i = 0; i < n; i++) {
	   		for (j = 0; j < 20000; j++)
			 _nop_();
	   }
}


/******************************主函数区域****************************/
void main(void)
{ 
	//配置P3.6为推挽输出模式
	//P3M0|=0x40;			//P3M0.6=1
	//P3M1&=0xBF;			//P3M1.6=0
	P2 =  0xfe;delay_s(2);
	WK2XXX_Init();	//初始化wk2xxx

	P2 = 0xfd;delay_s(2);
	//配置子串口的波特率
//	WK2XXX_UTx_Init(1,WK2XXX_BAUD_9600);	//子串口1波特率为14400bps
//	WK2XXX_UTx_Init(2,WK2XXX_BAUD_9600);	//子串口2波特率为14400bps
//	WK2XXX_UTx_Init(3,WK2XXX_BAUD_9600);	//子串口3波特率为14400bps
//	WK2XXX_UTx_Init(4,WK2XXX_BAUD_9600);	//子串口4波特率为14400bps
	
	P2 = 0xfb;delay_s(2);
//	
//	while (1) {
//		P0 = 1 << 0;delay_s(1);
//		WK2XXX_Write_REG_SendString(1, "hello1\r\n");
//		
//		P0 = 1 << 1;delay_s(1);
//		WK2XXX_Write_REG_SendString(2, "hello2\r\n");
//		
//		P0 = 1 << 2;delay_s(1);
//		WK2XXX_Write_REG_SendString(3, "hello3\r\n");
//		
//		P0 = 1 << 3;delay_s(1);
//		WK2XXX_Write_REG_SendString(4, "hello4\r\n");
//		
//	}

while(1);
}