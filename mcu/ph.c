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
	ph_iic_write_byte(PCF8591_ADDR);	//����д����
	ph_iic_wait_ack();

	ph_iic_write_byte(0x40); 	//����д��ַ
	ph_iic_wait_ack();

	ph_iic_start();
	ph_iic_write_byte(PCF8591_ADDR_R); 	//�������ģʽ
	ph_iic_wait_ack();

	v = ph_iic_read_byte(0);	//��ȡ�ֽ�
	ph_iic_stop();				//����һ��ֹͣ����

	v = -5.887* v * 5.0 / 255 + 21.677;  //ת��Ϊ��ѹֵ
	if (v >= 14)
		v = 14.0;
	else if (v < 0)
		v = 0;

	return v;
}
