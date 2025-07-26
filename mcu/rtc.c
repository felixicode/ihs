#include "STC89C5xRC.H"
#include "uart.h"
#include "wk2xxx.h"
#include "print.h"
#include "i2c.h"

#define uchar unsigned char
#define uint unsigned int

// DS1307地址定义
#define DS1307_ADDR 0xD0
#define DS1307_ADDR_R 0xD1
#define DS1307_ADDR_W 0xD0

#ifdef RTC_SET
static void ds1307_write_one_byte(u8 addr,u8 dat)
{				   	  	    																 
    iic_start();  
	iic_write_byte(DS1307_ADDR);	//发送写命令
	iic_wait_ack();
		   
    iic_write_byte(addr);	//发送写地址   
	iic_wait_ack(); 	 										  		   
	iic_write_byte(dat);	//发送字节    							   
	iic_wait_ack();  		    	   
    iic_stop();				//产生一个停止条件
	delay_ms(10);	 
}
void rtc_clear_halt(void)
{
	u8 addr = 0;
	u8 v = ds1307_read_one_byte(addr);
	v = v & 0x3f;
	ds1307_write_one_byte(addr, v);
}

void rtc_set_date_time(u8 n, u8 y, u8 r, u8 s, u8 f, u8 m)
{
	ds1307_write_one_byte(0, m);
	ds1307_write_one_byte(1, f);
	ds1307_write_one_byte(2, s);
	ds1307_write_one_byte(4, r);
	ds1307_write_one_byte(5, y);
	ds1307_write_one_byte(6, n);				
}

void rtc_set_week_day(u8 n)
{
	ds1307_write_one_byte(3, n);				
}
#endif


// DS1307从指定寄存器读一个字节
u8 ds1307_read_one_byte(u8 addr) {
	u8 temp = 0;
	iic_start();
	iic_write_byte(DS1307_ADDR);	//发送写命令
	iic_wait_ack();

	iic_write_byte(addr); 	//发送写地址
	iic_wait_ack();

	iic_start();
	iic_write_byte(DS1307_ADDR_R); 	//进入接收模式
	iic_wait_ack();

	temp=iic_read_byte(0);	//读取字节
	iic_stop();				//产生一个停止条件
	return temp;			//返回读取的数据
}

// 2025-07-23 01:23:45
void rtc_read(char *arr, char len)
{
	unsigned char i, tmp[7];

	if (len < 20) {
		print_str("Buffer is too small\r\n");
		return;
	}

	for (i = 0; i < 7; i++)
		tmp[i] = ds1307_read_one_byte(i);
	//print_str("RTC NewLoop: ");
	//for (i = 0; i < 7; i++) {
	//	print_num(tmp[i]);
	//	print_str(" ");
	//}
	//print_str("\r\n");
	sprintf(arr, "20%02x-%02x-%02x %02x:%02x:%02x",
		(int)tmp[6], (int)tmp[5], (int)tmp[4], (int)tmp[2], (int)tmp[1], (int)tmp[0]);
}