#ifndef __LCD_I2C_H__
#define __LCD_I2C_H__

#include "main.h"

void lcd_init(void);
void lcd_send_cmd(uint8_t cmd);
void lcd_send_data(uint8_t data);
void lcd_send_string(char *str);

#endif
