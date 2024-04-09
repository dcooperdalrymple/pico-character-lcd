#pragma once
#include "pico/stdlib.h"
#include "character_lcd_gpio.hpp"

class CharacterLCD_4Bit : public CharacterLCD_GPIO {

public:
    CharacterLCD_4Bit(uint8_t columns, uint8_t rows, uint rs, uint en, uint d4, uint d5, uint d6, uint d7);
    CharacterLCD_4Bit(uint8_t columns, uint8_t rows, DigitalInOut *rs, DigitalInOut *en, DigitalInOut *d4, DigitalInOut *d5, DigitalInOut *d6, DigitalInOut *d7);
    ~CharacterLCD_4Bit();

protected:
    void put(uint8_t value);
    void put(uint8_t value, bool char_mode);

private:
    DigitalInOut * d[4];

};
