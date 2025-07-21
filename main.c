#include <string.h>
#include "STC89C5xRC.H"
#include "intrins.h"
#include "print.h"
#include "ec.h"
#include "dtu.h"
#include "uart.h"
#include "wk2xxx.h"


void main(void)
{ 
	int ec = 0;
	float temp = 0;

	WK2XXX_Init();

	print_init();
	ec_init();
	dtu_init();

	P2 = 0xAA;

	while (1) {
		P2 = ~P2;

		ec_read(&ec, &temp);
		dtu_send(ec, temp, 7.5);

		delay_s(2);
	}
}