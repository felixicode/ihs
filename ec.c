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
#include "wk2xxx.h"

static void write_byte(char input)
{
	WK2XXX_Write_REG_SendByte(2,input);//使用子串口2发送字符串
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


