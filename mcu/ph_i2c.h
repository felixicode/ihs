#ifndef PH_I2C_H_
#define PH_I2C_H_
#include "delay.h"
void ph_iic_start(void);
void ph_iic_stop(void);
void ph_iic_write_byte(u8 dat);
u8 ph_iic_read_byte(u8 ack);
u8 ph_iic_wait_ack(void);
void ph_iic_ack(void);
void ph_iic_nack(void);

#endif