#include <reg52.h>
#include <string.h>
#include "intrins.h"
typedef unsigned char uchar;



sbit newTXD = P1^1;//模拟串口的发送端设为P2.1


void print_init()
{

	SCON  = 0x50;     // SCON: serail mode 1, 8-bit UART
	TMOD |= 0x21;     // T0工作在方式1，十六位定时
	PCON |= 0x80;     // SMOD=1;
	// 定时器0初始值，延时417us，目的是令模拟串口的波特率为4800bps fosc=11.0592MHz
	// 定时器0初始值，延时417us，目的是令模拟串口的波特率为4800bps fosc=11.0592MHz
	TH0 = (65536 - 192) / 256;
	TL0 = (65536 - 192) % 256;
}

void WaitTF0(void)
{
	while(!TF0);
	TF0=0;
	// 定时器0初始值，延时417us，目的是令模拟串口的波特率为4800bps fosc=11.0592MHz
	// 定时器0初始值，延时417us，目的是令模拟串口的波特率为4800bps fosc=11.0592MHz
   	TH0 = (65536 - 192) / 256;
	TL0 = (65536 - 192) % 256;
}

void write_byte(uchar input)
{

	//发送启始位
	uchar j=8;

	newTXD=(bit)0;
	WaitTF0();
	
	//发送8位数据位
	while(j--)
	{
	   newTXD=(bit)(input&0x01);      //先传低位
	   WaitTF0();
	   input=input>>1;
	}
	
	//发送校验位(无)
	//发送结束位
	newTXD=(bit)1;
	WaitTF0();
	TR0=0;
}

void print_str(const char *str)
{
	int i, len = strlen(str);

	for (i = 0; i <len; i++)
		   write_byte(str[i]);
}

void print_l2c(long n)
{
	int i = 0, j;	
	char c[20] = {'0'};
	while(n)
	{
		c[i++] = ((n % 10) +'0');
		n /= 10;
	}
	for(j = i - 1; j >= 0; j--)
		WByte(c[j]);
}