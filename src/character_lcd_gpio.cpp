#include "character_lcd_gpio.hpp"

CharacterLCD_GPIO::CharacterLCD_GPIO(uint8_t columns, uint8_t rows, uint rs, uint en) : CharacterLCD(columns, rows) {
    this->rs = new DigitalInOut_GPIO(rs);
    this->rs->set_dir(true);

    this->en = new DigitalInOut_GPIO(en);
    this->en->set_dir(true);
};

CharacterLCD_GPIO::CharacterLCD_GPIO(uint8_t columns, uint8_t rows, DigitalInOut * rs, DigitalInOut * en) : CharacterLCD(columns, rows) {
    this->rs = rs;
    this->rs->set_dir(true);

    this->en = en;
    this->en->set_dir(true);
};

CharacterLCD_GPIO::~CharacterLCD_GPIO() {
    delete this->rs;
    delete this->en;
};

void CharacterLCD_GPIO::pulse_enable() {
    this->en->put(false);
    sleep_us(1);
    this->en->put(true);
    sleep_us(1);
    this->en->put(false);
    sleep_us(1);
};
