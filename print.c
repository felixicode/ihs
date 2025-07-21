#include <reg52.h>
#include <string.h>
#include "intrins.h"
#include "uart.h"
#include "wk2xxx.h"


void print_init(void)
{
	WK2XXX_UTx_Init(IHS_UART_PRINT,WK2XXX_BAUD_9600);	//子串口1波特率为14400bps
}

void write_byte(char input)
{
	WK2XXX_Write_REG_SendByte(IHS_UART_PRINT,input);//使用子串口2发送字符串
}

void print_str(const char *str)
{
	WK2XXX_Write_REG_SendString(IHS_UART_PRINT, str);
}

//void print_int(int n)
//{
//	int i = 0, j;	
//	char c[20] = {'0'};
//
//	if (n == 0) {
//		write_byte('0');
//		return;
//	}
//	while(n)
//	{
//		c[i++] = ((n % 10) +'0');
//		n /= 10;
//	}
//	for(j = i - 1; j >= 0; j--)
//		write_byte(c[j]);
//}