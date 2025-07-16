#include <reg52.h>
#include <string.h>
#include "intrins.h"
#include "uart.h"
typedef unsigned char uchar;

sbit UART_TX = P1^1;
sbit UART_RX = P1^0;

void uart_init()
{

	SCON  = 0x50;     // SCON: serail mode 1, 8-bit UART
	TMOD |= 0x21;     // T0�����ڷ�ʽ1��ʮ��λ��ʱ
	PCON |= 0x80;     // SMOD=1;
	// ��ʱ��0��ʼֵ����ʱ417us��Ŀ������ģ�⴮�ڵĲ�����Ϊ4800bps fosc=11.0592MHz
	// ��ʱ��0��ʼֵ����ʱ417us��Ŀ������ģ�⴮�ڵĲ�����Ϊ4800bps fosc=11.0592MHz
	TH0 = (65536 - 192) / 256;
	TL0 = (65536 - 192) % 256;
}

void uart_sleep_4800(void)
{

	while(!TF0);
	TF0=0;
		// ��ʱ��0��ʼֵ����ʱ417us��Ŀ������ģ�⴮�ڵĲ�����Ϊ4800bps fosc=11.0592MHz
	// ��ʱ��0��ʼֵ����ʱ417us��Ŀ������ģ�⴮�ڵĲ�����Ϊ4800bps fosc=11.0592MHz
   	TH0 = (65536 - 192) / 256;
	TL0 = (65536 - 192) % 256;

	
}

void write_byte(uchar input)
{
	uchar i = 8;
	
	// start timer
	TR0 = 1;
	
	// start bit
	UART_TX=(bit)0;
	uart_sleep_4800();
	
	//data bit
	while(i--)
	{
	   UART_TX =(bit)(input & 0x01);      //�ȴ���λ
	   uart_sleep_4800();
	   input >>= 1;
	}
	
	// stop bit
	UART_TX=(bit)1;
	uart_sleep_4800();
	
	// stop timer
	TR0=0;
}

void print_str(const char *str)
{
	int i, len = strlen(str);

	uart_init();
	for (i = 0; i <len; i++)
		   write_byte(str[i]);
}

void print_int(int n)
{
	int i = 0, j;	
	char c[20] = {'0'};

	uart_init();
	if (n == 0) {
		write_byte('0');
		return;
	}
	while(n)
	{
		c[i++] = ((n % 10) +'0');
		n /= 10;
	}
	for(j = i - 1; j >= 0; j--)
		write_byte(c[j]);
}