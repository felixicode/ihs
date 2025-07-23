#include <reg52.h>
#include <string.h>
#include "intrins.h"
#include "uart.h"
#include "wk2xxx.h"


void print_init(void)
{
	WK2XXX_UTx_Init(IHS_UART_PRINT,WK2XXX_BAUD_9600);
}

void print_str(const char *str)
{
	WK2XXX_Write_REG_SendString(IHS_UART_PRINT, str);
}

#if 1
void print_num(int n)
{
	xdata char str[20] = {'0'};

	sprintf(str, "%x", n);
	WK2XXX_Write_REG_SendString(IHS_UART_PRINT, str);
}

void print_float(float n)
{
	xdata char str[20] = {'0'};

	sprintf(str, "%f", n);
	WK2XXX_Write_REG_SendString(IHS_UART_PRINT, str);
}

void print_charx(unsigned char n)
{
	xdata char str[20] = {'0'};

	sprintf(str, "0x%X", (unsigned int)n);
	WK2XXX_Write_REG_SendString(IHS_UART_PRINT, str);
}
#endif