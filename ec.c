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
#include "wk2xxx.h"

static void write_byte(char input)
{
	WK2XXX_Write_REG_SendByte(2,input);//ʹ���Ӵ���2�����ַ���
}

static char read_byte(void)
{
	return WK2XXX_Write_REG_ReceiveByte(2);
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


