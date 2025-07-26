#include "STC89C5xRC.H"
#include "uart.h"
#include "wk2xxx.h"
#include "print.h"
#include "ph_i2c.h"

//
#define PCF8591_ADDR	0x90
#define PCF8591_ADDR_R	0x91

float ph_read(void)
{
	u8 v = 0;

	ph_iic_start();
	ph_iic_write_byte(PCF8591_ADDR);	//发送写命令
	ph_iic_wait_ack();

	ph_iic_write_byte(0x40); 	//发送写地址
	ph_iic_wait_ack();

	ph_iic_start();
	ph_iic_write_byte(PCF8591_ADDR_R); 	//进入接收模式
	ph_iic_wait_ack();

	v = ph_iic_read_byte(0);	//读取字节
	ph_iic_stop();				//产生一个停止条件

	v = -5.887* v * 5.0 / 255 + 21.677;  //转换为电压值
	if (v >= 14)
		v = 14.0;
	else if (v < 0)
		v = 0;

	return v;
}
