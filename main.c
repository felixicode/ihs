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
	long ec, temp; 
	UartInit();
	//print_str("111ec_init       ");
	//ec_init();
	//print_str("222ec_init       ");
	for(;;)
	{
		//ec = 1123;
		//temp = 33;
		delay_s(10);
		//print_str("111_ec_read\n");
		//ec_read(&ec, &temp);
		//print_str("222_ec_read\n");
		print_str("ec  : ");
		print_l2c(ec);
		print_str("   ");
		print_str("temp: ");
		print_l2c(temp);
		print_str("   ");
	}
	while(1);
}