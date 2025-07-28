#include "lcd_i2c.h"

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_I2C1_Init();  // Ensure hi2c1 is configured properly

  lcd_init();
  lcd_send_string("Hello Boss!");
  lcd_send_cmd(0xC0);  // 2nd line
  lcd_send_string("STM32 LCD I2C");

  while (1) 
  {
  }
}
