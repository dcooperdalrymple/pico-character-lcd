#include <stdio.h>
#include "pico/stdlib.h"
#include "character_lcd_4bit.hpp"
#include <string>

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

    lcd.enable_horizontal_graph();

    lcd.clear();
    lcd.cursor(true);
    lcd.blink(true);
    lcd.cursor_position(15, 0);
    
    lcd.write("Hello, world!");

    uint i = 0;
    std::string s;
    while (true) {
        s = std::to_string(++i);
        lcd.write(s.c_str(), 8, 1, 8, true);
        lcd.write_horizontal_graph(i % 5 * 63, 0, 1, 8);
        lcd.update(true);
        sleep_ms(1000);
    }

    return 0;
}
