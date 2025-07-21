#include "uart.h"
#include "wk2xxx.h"


void dtu_init(void)
{
	WK2XXX_UTx_Init(IHS_UART_DTU,WK2XXX_BAUD_4800);	//子串口1波特率为14400bps
}

int format_json(float ph, int ec, int temp, char* str)
{
#if 0
	return sprintf(str, "{" \
		"\"PH\":\"%.1f\"," \
		"\"EC\":\"%d\"," \
		"\"TEMP\":\"%.1f\"" \
	"}", ph, ec, temp);	
#endif	
	return sprintf(str, "{" \
		"\"PH\":\"%.1f\"," \
	"}", ph+ec+temp);	
}

void dtu_send(int ec, int temp, float ph)
{
	char str[20];
	
	format_json(ph, ec, temp, str);
	
	WK2XXX_Write_REG_SendString(IHS_UART_DTU, str);
}