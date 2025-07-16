 /**********************************************************************************
 * ����    ��STC89C52RC, ����11.0592MHz, �����ʣ�9600, ���ڶ�ȡ��·EC�絼��ģ��Ũ������ 
 * Ӳ�����ӣ�        
 * LCD1602��RS -> P2.5; RW -> P2.6; E -> P2.7;
 *          D0~D7 -> P0��
 * ��·EC�絼��ģ�飺3.3V -> 3.3V; RX -> 3.1; TX -> P3.0; GND -> GND;  
 * ����������������ӵ�·EC�絼��ģ���ȡŨ�����ݣ���LCD1602Һ������ʾŨ������
 * ʹ��˵���������غó����ٽ���
**********************************************************************************/
#include "reg51.h"
#include "intrins.h"
#include "ec.h"

sbit EC_UART_TX = P1^3;
sbit EC_UART_RX = P1^2;

static void uart_init()
{

	SCON  = 0x50;     // SCON: serail mode 1, 8-bit UART
	TMOD |= 0x21;     // T0�����ڷ�ʽ1��ʮ��λ��ʱ
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
	   EC_UART_TX =(bit)(input & 0x01);      //�ȴ���λ
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
    while (EC_UART_RX);    // �ȴ���ʼλ���͵�ƽ��
	TR0 = 1;
    uart_sleep_9600();
    
    for (i = 0; i < 8; i++) // ���� 8 λ����
    {
        dat >>= 1;          // ����׼��������һλ
        if (EC_UART_RX) dat |= 0x80; // ��� RX=1�����λ�� 1
       uart_sleep_9600();
    }
    
    while (!EC_UART_RX);   // �ȴ�ֹͣλ���ߵ�ƽ��
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


