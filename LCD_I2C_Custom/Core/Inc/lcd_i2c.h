#ifndef __LCD_I2C_H__
#define __LCD_I2C_H__

#include "stm32f1xx_hal.h"

#define LCD_BACKLIGHT 0x08
#define LCD_ENABLE    0x04
#define LCD_RW        0x02
#define LCD_RS        0x01

void lcd_init(I2C_HandleTypeDef *hi2c);
void lcd_send_cmd(uint8_t cmd);
void lcd_send_data(uint8_t data);
void lcd_send_string(char *str);
void lcd_set_cursor(uint8_t row, uint8_t col);

#endif
