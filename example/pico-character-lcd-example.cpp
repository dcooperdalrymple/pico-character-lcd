#include <stdio.h>
#include "pico/stdlib.h"
#include "character_lcd_4bit.hpp"

#define LCD_COLS 16
#define LCD_ROWS 2
#define LCD_RS   2
#define LCD_EN   3
#define LCD_D4   4
#define LCD_D5   5
#define LCD_D6   6
#define LCD_D7   7

static CharacterLCD_4Bit lcd(LCD_COLS, LCD_ROWS, LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

int main() {
    stdio_init_all();
    printf("Pico C/C++ Character LCD Library Example\n");
    lcd.write("Hello, world!");
    return 0;
}
