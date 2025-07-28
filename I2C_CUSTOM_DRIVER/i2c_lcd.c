#include "stm32f1xx_hal.h"
#include "lcd_i2c.h"

extern I2C_HandleTypeDef hi2c1;

#define LCD_ADDR  0x4E  // PCF8574T I2C address (shifted left)
#define BACKLIGHT 0x08  // Bit 3 = 1 → backlight ON

void lcd_send_nibble(uint8_t nibble, uint8_t rs)
{
    uint8_t data = 0;

    data |= (nibble & 0x0F) << 0;      // D4-D7 to P0-P3
    if (rs) data |= (1 << 7);          // RS = P7
    data |= BACKLIGHT;                 // Backlight ON
    data |= (1 << 5);                  // EN = P5 = 1 (Enable High)

    HAL_I2C_Master_Transmit(&hi2c1, LCD_ADDR, &data, 1, HAL_MAX_DELAY);

    // EN = 0 (falling edge)
    data &= ~(1 << 5);
    HAL_I2C_Master_Transmit(&hi2c1, LCD_ADDR, &data, 1, HAL_MAX_DELAY);

    HAL_Delay(1);
}

void lcd_send_cmd(uint8_t cmd)
{
    uint8_t high_nibble = (cmd >> 4) & 0x0F;
    uint8_t low_nibble  = cmd & 0x0F;

    lcd_send_nibble(high_nibble, 0); // RS = 0 → Command
    lcd_send_nibble(low_nibble,  0);
}

void lcd_send_data(uint8_t data)
{
    uint8_t high_nibble = (data >> 4) & 0x0F;
    uint8_t low_nibble  = data & 0x0F;

    lcd_send_nibble(high_nibble, 1); // RS = 1 → Data
    lcd_send_nibble(low_nibble,  1);
}

void lcd_send_string(char *str)
{
    while (*str)
    {
        lcd_send_data(*str++);
    }
}

void lcd_init(void)
{
    HAL_Delay(50);  // Wait for LCD to power up

    lcd_send_cmd(0x33);  // Init 1
    lcd_send_cmd(0x32);  // Init 2
    lcd_send_cmd(0x28);  // Function set: 4-bit, 2 line, 5x8
    lcd_send_cmd(0x0C);  // Display ON, Cursor OFF
    lcd_send_cmd(0x06);  // Entry mode: Increment cursor
    lcd_send_cmd(0x01);  // Clear display
    HAL_Delay(2);
}
