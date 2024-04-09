#pragma once
#include "character_lcd_4bit.hpp"
#include "mcp23008.hpp"

const uint8_t LCD_I2C_RS       = 1;
const uint8_t LCD_I2C_EN       = 2;
const uint8_t LCD_I2C_D4       = 3;
const uint8_t LCD_I2C_D5       = 4;
const uint8_t LCD_I2C_D6       = 5;
const uint8_t LCD_I2C_D7       = 6;

class CharacterLCD_I2C : public CharacterLCD_4Bit {

public:
    CharacterLCD_I2C(uint8_t columns, uint8_t rows, i2c_inst_t *i2c, uint sda, uint scl, uint8_t address);
    CharacterLCD_I2C(uint8_t columns, uint8_t rows, i2c_inst_t *i2c, uint sda, uint scl);
    CharacterLCD_I2C(uint8_t columns, uint8_t rows);
    ~CharacterLCD_I2C();

private:
    MCP23008 *mcp;

};
