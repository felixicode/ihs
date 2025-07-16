 /**********************************************************************************
 * 描述    ：STC89C52RC, 晶振11.0592MHz, 波特率：9600, 串口读取单路EC电导率模块浓度数据 
 * 硬件连接：        
 * LCD1602：RS -> P2.5; RW -> P2.6; E -> P2.7;
 *          D0~D7 -> P0口
 * 单路EC电导率模块：3.3V -> 3.3V; RX -> 3.1; TX -> P3.0; GND -> GND;  
 * 功能描述：串口外接单路EC电导率模块读取浓度数据，在LCD1602液晶屏显示浓度数据
 * 使用说明：先下载好程序再接线
**********************************************************************************/
#include "reg51.h"
#include "intrins.h"
#include "ec.h"

sbit EC_UART_TX = P1^3;
sbit EC_UART_RX = P1^2;

static void uart_init()
{

	SCON  = 0x50;     // SCON: serail mode 1, 8-bit UART
	TMOD |= 0x21;     // T0工作在方式1，十六位定时
	PCON |= 0x80;     // SMOD=1;

	TH0 = (65536 - 95) / 256;
	TL0 = (65536 - 95) % 256;
}

static void uart_sleep_9600(void)
{

	while(!TF0);
	TF0=0;
   	TH0 = (65536 - 96) / 256;
	TL0 = (65536 - 96) % 256;
}


static void write_byte(char input)
{
	char i = 8;
	
	// start timer
	TR0 = 1;
	
	// start bit
	EC_UART_TX=(bit)0;
	uart_sleep_9600();
	
	//data bit
	while(i--)
	{
	   EC_UART_TX =(bit)(input & 0x01);      //先传低位
	   uart_sleep_9600();
	   input >>= 1;
	}
	
	// stop bit
	EC_UART_TX=(bit)1;
	uart_sleep_9600();
	
	// stop timer
	TR0=0;
}

static char read_byte(void)
{
	char i, dat = 0;
	
	// start timer
    while (EC_UART_RX);    // 等待起始位（低电平）
	TR0 = 1;
    uart_sleep_9600();
    
    for (i = 0; i < 8; i++) // 接收 8 位数据
    {
        dat >>= 1;          // 右移准备接收下一位
        if (EC_UART_RX) dat |= 0x80; // 如果 RX=1，最高位置 1
       uart_sleep_9600();
    }
    
    while (!EC_UART_RX);   // 等待停止位（高电平）
	uart_sleep_9600();
	
	// stop timer
	TR0=0;
	
    return dat;
}

static void ec_check(int *ec, int *temp)
{
	char c;
	
	// send frame head
	write_byte(0xA0);
	
	write_byte(0x00);	
	write_byte(0x00);
	write_byte(0x00);
	write_byte(0x00);
	
	// send frame tail
	write_byte(0xA0);
	

	// read frame head
	c = read_byte();
	if (c != 0xAA) {
		*ec = *temp = 9999;
		return;
	}
	
	// read diandao
	*ec = read_byte();
	*ec <<= 8;
	*ec |= read_byte();
	
	// read temperatur
	*temp = read_byte();
	*temp <<= 8;
	*temp |= read_byte();
	
	// read frame tail
	c = read_byte();
	if (c != 0x40) {
		*ec = *temp = 9998;
		return;
	}
}

void ec_read(int *ec, int *temp)
{
	uart_init();
	ec_check(ec, temp);	
}


