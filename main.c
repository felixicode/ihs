//#include <reg52.h>
#include <string.h>
//#include "STC8H.h"
#include "STC89C5xRC.H"
#include "intrins.h"
#include "print.h"
#include "ec.h"
#include "dtu.h"

#include "uart.h"
#include "wk2xxx.h"

void delay_s(unsigned int n)
{
	   unsigned int i, j;

	   for (i = 0; i < n; i++) {
	   		for (j = 0; j < 20000; j++)
			 _nop_();
	   }
}


/******************************主函数区域****************************/
void main(void)
{ 
	int ec = 0, temp = 0;

	P2 =  0xfe;delay_s(2);
	WK2XXX_Init();	//初始化wk2xxx

	// init print
	print_init();
	ec_init();
	dtu_init();	
	P2 = 0xfd;delay_s(2);
	
	while (1) {
		P0 = 1 << 0;delay_s(1);
		print_str("hello uart\r\n");
		ec_read(&ec, &temp);
		print_str("ec  : ");
		print_num(ec);
		print_str("\r\n");
		print_str("temp: ");
		print_num(temp);
		print_str("\r\n");
		dtu_send(ec, temp, 7);
		
	}

while(1);
}