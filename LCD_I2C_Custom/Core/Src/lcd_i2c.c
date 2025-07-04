/*
 * lcd_i2c.c
 *
 *  Created on: Jul 3, 2025
 *      Author: Akshay
 */

#include "lcd_i2c.h"
#include "stm32f1xx_hal.h"
#include "string.h"

#define LCD_ADDR (0x27 << 1)
static I2C_HandleTypeDef *_lcd_i2c;

void lcd_send_internal(uint8_t data, uint8_t mode)
{
    uint8_t upper = data & 0xF0;
    uint8_t lower = (data << 4) & 0xF0;

    uint8_t data_arr[4];
    data_arr[0] = upper | mode | LCD_BACKLIGHT | LCD_ENABLE;
    data_arr[1] = upper | mode | LCD_BACKLIGHT;
    data_arr[2] = lower | mode | LCD_BACKLIGHT | LCD_ENABLE;
    data_arr[3] = lower | mode | LCD_BACKLIGHT;

    HAL_I2C_Master_Transmit(_lcd_i2c, LCD_ADDR, data_arr, 4, HAL_MAX_DELAY);
    HAL_Delay(1);
}

void lcd_send_cmd(uint8_t cmd) {
    lcd_send_internal(cmd, 0);
}

void lcd_send_data(uint8_t data) {
    lcd_send_internal(data, LCD_RS);
}

// char *str = "HELLO"; 
// *str = H
// *str + 1 = E 
// *str == \0
void lcd_send_string(char *str) {
    while (*str) {
        lcd_send_data((uint8_t)(*str));
        str++;
    }
}

void lcd_set_cursor(uint8_t row, uint8_t col) {
    uint8_t addr = (row == 0) ? (0x80 + col) : (0xC0 + col);
    lcd_send_cmd(addr);
}

void lcd_init(I2C_HandleTypeDef *hi2c)
{
    _lcd_i2c = hi2c;
    HAL_Delay(50);
    lcd_send_cmd(0x33);
    lcd_send_cmd(0x32);
    lcd_send_cmd(0x28);
    lcd_send_cmd(0x0C);
    lcd_send_cmd(0x06);
    lcd_send_cmd(0x01);
    HAL_Delay(5);
}

