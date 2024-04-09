#pragma once
#include "pico/stdlib.h"
#include "character_lcd_gpio.hpp"

class CharacterLCD_8Bit : public CharacterLCD_GPIO {

public:
    CharacterLCD_8Bit(uint8_t columns, uint8_t rows, uint rs, uint en, uint d0, uint d1, uint d2, uint d3, uint d4, uint d5, uint d6, uint d7);
    CharacterLCD_8Bit(uint8_t columns, uint8_t rows, DigitalInOut *rs, DigitalInOut *en, DigitalInOut *d0, DigitalInOut *d1, DigitalInOut *d2, DigitalInOut *d3, DigitalInOut *d4, DigitalInOut *d5, DigitalInOut *d6, DigitalInOut *d7);
    ~CharacterLCD_8Bit();

protected:
    void put(uint8_t value);
    void put(uint8_t value, bool char_mode);

private:
    DigitalInOut * d[8];

};
