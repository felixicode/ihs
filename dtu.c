#include "STC89C5xRC.H"
#include "uart.h"
#include "wk2xxx.h"
#include "print.h"
#include "dtu.h"

sbit DTU_TO_MQTT = P3^7; // 将P3.7 接GND 会向MQTT发消息, 否则不发送

void dtu_init(void)
{
	WK2XXX_UTx_Init(IHS_UART_DTU,WK2XXX_BAUD_4800);	//子串口1波特率为14400bps
}

static void format_json(int ec, float temp, float ph, char *arr , char *str)
{
	int len;

	len = sprintf(str,
		"{" \
			"\"PH\":\"%.1f\"," \
			"\"EC\":\"%d\"," \
			"\"TEMP\":\"%.1f\"," \
		, (float)ph, (int)ec, (float)temp);

	sprintf(str + len, 
			"\"TIME\":\"%s\""\
		"}", arr);
}

void dtu_send(int ec, float temp, float ph, char *arr)
{
	xdata char str[96];

	format_json(ec, temp, ph, arr, str);
	print_str(str);
	print_str("\r\n");

	if (DTU_TO_MQTT == 0)
		WK2XXX_Write_REG_SendString(IHS_UART_DTU, str);
}