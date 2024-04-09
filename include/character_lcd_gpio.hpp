#pragma once
#include "character_lcd.hpp"
#include "digitalinout.hpp"

class CharacterLCD_GPIO : public CharacterLCD {

public:
    CharacterLCD_GPIO(uint8_t columns, uint8_t rows, uint rs, uint en);
    CharacterLCD_GPIO(uint8_t columns, uint8_t rows, DigitalInOut * rs, DigitalInOut * en);
    ~CharacterLCD_GPIO();

protected:
    DigitalInOut * rs;
    DigitalInOut * en;
    void pulse_enable();

    virtual void put(uint8_t value) { };
    virtual void put(uint8_t value, bool char_mode) { };

};
