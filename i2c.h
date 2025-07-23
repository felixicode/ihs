#ifndef _iic_H
#define _iic_H
#include "delay.h"

void iic_start(void);
void iic_stop(void);
void iic_write_byte(u8 txd);
u8 iic_read_byte(u8 ack);
u8 iic_wait_ack(void);
void iic_ack(void);
void iic_nack(void);

#endif