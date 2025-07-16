#include <reg52.h>
#include <string.h>
#include "intrins.h"
#include "uart.h"
#include "ec.h"

void delay_s(unsigned int n)
{
	   unsigned int i, j;

	   for (i = 0; i < n; i++) {
	   		for (j = 0; j < 20000; j++)
			 _nop_();
	   }
}

void main()
{
	int ec, temp; 

	print_str("start\r\n");

	for(;;)
	{
		delay_s(10);
		print_str("111_ec_read\r\n");
		ec_read(&ec, &temp);
		print_str("222_ec_read\r\n");
		print_str("ec  : ");
		print_int(ec);
		print_str("\r\n");
		print_str("temp: ");
		print_int(temp);
		print_str("\r\n");
	}
}