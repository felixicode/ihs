 /**********************************************************************************
 * ����    ��STC89C52RC, ����11.0592MHz, �����ʣ�9600, ���ڶ�ȡ��·EC�絼��ģ��Ũ������ 
 * Ӳ�����ӣ�        
 * LCD1602��RS -> P2.5; RW -> P2.6; E -> P2.7;
 *          D0~D7 -> P0��
 * ��·EC�絼��ģ�飺3.3V -> 3.3V; RX -> 3.1; TX -> P3.0; GND -> GND;  
 * ����������������ӵ�·EC�絼��ģ���ȡŨ�����ݣ���LCD1602Һ������ʾŨ������
 * ʹ��˵���������غó����ٽ���
**********************************************************************************/
#include <reg52.h>
#include "intrins.h"
#include "wk2xxx.h"

void ec_init(void)
{
	WK2XXX_UTx_Init(IHS_UART_EC,WK2XXX_BAUD_9600);	//�Ӵ���1������Ϊ14400bps
}

static void write_byte(char input)
{
	WK2XXX_Write_REG_SendByte(IHS_UART_EC, input);//ʹ���Ӵ���2�����ַ���
}

static char read_byte(void)
{
	return WK2XXX_Write_REG_ReceiveByte(IHS_UART_EC);
}

void ec_read(int *ec, int *temp)
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
	delay_ms(100);

	// read frame head
	c = read_byte();
	if (c != 0xAA) {
		*ec = c;
		*temp = 99;
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


