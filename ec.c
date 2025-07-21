#include <reg52.h>
#include "intrins.h"
#include "wk2xxx.h"
#include "print.h"

void ec_init(void)
{
	WK2XXX_UTx_Init(IHS_UART_EC,WK2XXX_BAUD_9600);
}

static void write_byte(u8 input)
{
	WK2XXX_Write_REG_SendByte(IHS_UART_EC, input);
}

static u8 read_byte(void)
{
	return WK2XXX_Write_REG_ReceiveByte(IHS_UART_EC);
}

void ec_read(int *ec, float *temp)
{
	unsigned char c;
	unsigned int wd;

	UART_num=6;
	UART_Rflag=0;
	*ec = *temp = 0;
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

	if (*ec > 3000)
		*ec = 3000;

	// read temperatur
	wd = read_byte();
	wd<<= 8;
	wd |= read_byte();
	*temp = (float)wd / 100.0;

	// read frame tail
	c = read_byte();
#if 0 // debug
	print_str("EC NewLoop: ");
	for (i = 0; i < 6; i++) {
		c = read_byte();
		print_charx(c);
		print_str(" ");
	}
	print_str("\r\n");
#endif
}


