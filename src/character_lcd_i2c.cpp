#include "character_lcd_i2c.hpp"

CharacterLCD_I2C::CharacterLCD_I2C(uint8_t columns, uint8_t rows, i2c_inst_t *i2c, uint sda, uint scl, uint8_t address)
    : mcp(new MCP23008(i2c, sda, scl, address)),
      CharacterLCD_4Bit(columns, rows, mcp->get_pin(LCD_I2C_RS), mcp->get_pin(LCD_I2C_EN), mcp->get_pin(LCD_I2C_D4), mcp->get_pin(LCD_I2C_D5), mcp->get_pin(LCD_I2C_D6), mcp->get_pin(LCD_I2C_D7)) {
};

CharacterLCD_I2C::CharacterLCD_I2C(uint8_t columns, uint8_t rows, i2c_inst_t *i2c, uint sda, uint scl)
    : mcp(new MCP23008(i2c, sda, scl)),
      CharacterLCD_4Bit(columns, rows, mcp->get_pin(LCD_I2C_RS), mcp->get_pin(LCD_I2C_EN), mcp->get_pin(LCD_I2C_D4), mcp->get_pin(LCD_I2C_D5), mcp->get_pin(LCD_I2C_D6), mcp->get_pin(LCD_I2C_D7)) {
};

CharacterLCD_I2C::CharacterLCD_I2C(uint8_t columns, uint8_t rows)
    : mcp(new MCP23008()),
      CharacterLCD_4Bit(columns, rows, mcp->get_pin(LCD_I2C_RS), mcp->get_pin(LCD_I2C_EN), mcp->get_pin(LCD_I2C_D4), mcp->get_pin(LCD_I2C_D5), mcp->get_pin(LCD_I2C_D6), mcp->get_pin(LCD_I2C_D7)) {
};

CharacterLCD_I2C::~CharacterLCD_I2C() {
    delete this->mcp;
};
