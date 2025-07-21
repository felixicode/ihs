/**
 * Intelligent Hydroponic System - Base On STC89C52 MCU
 *
 * Support List:
 *   Sensor: EC, Temperature
 *   4G DTU MQTT
 *
 * Todo: RTC(Real-Time Clock), Relay¼ÌµçÆ÷
 *
 * Date: 2025-07-22
 * Author: Felix Zhang <felixicode@163.com>
 */

#include <string.h>
#include "STC89C5xRC.H"
#include "intrins.h"
#include "print.h"
#include "ec.h"
#include "dtu.h"
#include "uart.h"
#include "wk2xxx.h"

#define VERSION "Version: IHS - v250722"

void main(void)
{ 
	int ec = 0;
	float temp = 0;

	WK2XXX_Init();

	print_init();
	ec_init();
	dtu_init();

	print_str("Welcome to Intelligent Hydroponic System\r\n");
	print_str("Author: Felix Zhang <felixicode@163.com>\r\n"); 
	print_str(VERSION"\r\n\r\n");


	P2 = 0xAA;

	while (1) {
		P2 = ~P2;

		ec_read(&ec, &temp);
		dtu_send(ec, temp, 7.5);

		delay_s(2);
	}
}